#pragma once

#include <string>
#include <regex>

#include <mfl/out.hpp>
#include <mfl/util.hpp>

#include "config_manager.hpp"
#include "executor/executor_manager_parser.hpp"

namespace ConfigParser {

  struct Line {
  private:
    static const std::regex REGEX;
    bool child = false;

  public:
    int indentation = -1;
    std::string key = "";
    std::string value = "";

    Line() = default;

    bool popChild() {
      if (child) {
        child = false;
        indentation++;
        return true;
      }
      return false;
    }

    Line & operator=(const std::string & rawLine) noexcept {
      indentation = 0;
      int size = mfl::util::safeCast<int>(rawLine.size());
      for (int i = 0; i < size; ++i) {
        if (!std::isspace(rawLine[i])) {
          if (rawLine[i] == '#') {
            indentation = -1;
            child = false;
            key = "";
            value = "";
            return *this;
          }
          indentation = i;
          break;
        }
      }

      if (indentation == size) {
        indentation = -1;
        child = false;
        key = "";
        value = "";
        return *this;
      }

      std::smatch match;
      if (!std::regex_match(rawLine, match, REGEX)) {
        child = false;
        key = "";
        value = "";
        return *this;
      }

      child = match[2] == "-";
      key = match[3];
      value = match[5];
      return *this;
    }
  };

  template <typename Stream>
  struct StreamReader {
  private:
    Stream mStream;

  public:
    Line line;
    int lineNumber = 0;
    std::string error = "";

    StreamReader(Stream & stream) : mStream(std::move(stream)) {}

    bool readNext(int expectedIndentation) {
      std::string buffer;
      while (std::getline(mStream, buffer)) {
        lineNumber++;
        line = buffer;

        if (line.indentation < 0) {
          continue;
        }

        if (line.indentation > expectedIndentation) {
          error = fmt::format("Wrong indentation. Was expecting {:d} and got {:d}",
                              expectedIndentation,
                              line.indentation);
          return false;
        }

        if (line.key.empty()) {
          error = "Could not parse line";
          return false;
        }

        return true;
      }

      return false;
    }

  };

  struct Object {
    static constexpr auto EXECUTORS = "executors";
  };

  template <typename Stream>
  bool parse(Stream & stream, ConfigManager & configManager) {
    int indentation = 0;

    StreamReader<Stream> reader(stream);

    if (reader.readNext(indentation)) {
      while (reader.line.indentation == indentation) {
        if (reader.line.key == Object::EXECUTORS) {
          if (!ExecutorManagerParser::parse(reader,
                                            configManager.executorManager,
                                            indentation + 1)) {
            break;
          }
        } else {
          reader.error = "Unrecognized base entry";
          break;
        }
      }
    }

    if (!reader.error.empty()) {
      mfl::out::println(stderr, "Failed to parse config at line: {:d}", reader.lineNumber);
      mfl::out::println(stderr, "  Error: {:s}", reader.error);
      if (!reader.line.key.empty()) {
        mfl::out::println(stderr, "  Key: {:s}", reader.line.key);
      }
      if (!reader.line.value.empty()) {
        mfl::out::println(stderr, "  Value: {:s}", reader.line.value);
      }
      return false;
    }

    return true;
  }

  template <typename Stream>
  bool save(Stream & stream, const ConfigManager & configManager) {
    stream << Object::EXECUTORS << std::endl;
    if (!ExecutorManagerParser::save(stream, configManager.executorManager, 1)) {
      return false;
    }

    return true;
  }
}
