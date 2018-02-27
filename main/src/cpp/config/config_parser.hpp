#pragma once

#include <string>
#include <sstream>

#include <mfl/out.hpp>

#include "config_manager.hpp"
#include "executor/executor_manager_parser.hpp"

class ConfigParser {
private:

  struct Line {
  private:
    static const std::regex REGEX;
    bool listItem = false;

  public:
    int indentation = -1;
    std::string key = "";
    std::string value = "";

    Line() = default;

    bool popListItem() {
      if (listItem) {
        listItem = false;
        indentation++;
        return true;
      }
      return false;
    }

    Line & operator=(const std::string & rawLine) noexcept {
      indentation = 0;
      for (int i = 0; i < rawLine.size(); ++i) {
        if (!std::isspace(rawLine[i])) {
          if (rawLine[i] == '#') {
            indentation = -1;
            listItem = false;
            key = "";
            value = "";
            return *this;
          }
          indentation = i;
          break;
        }
      }

      if (indentation == rawLine.size()) {
        indentation = -1;
        listItem = false;
        key = "";
        value = "";
        return *this;
      }

      std::smatch match;
      if (!std::regex_match(rawLine, match, REGEX)) {
        listItem = false;
        key = "";
        value = "";
        return *this;
      }

      listItem = match[2] == "-";
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
    static constexpr auto FOO = "foo";
    static constexpr auto BAR = "bar";
  };

  template <typename StreamReader>
  void parseBaseConfig(StreamReader & reader,
                       ConfigManager & configManager) {
    int indentation = 0;

    if (!reader.readNext(indentation)) {
      return;
    }

    while (reader.line.indentation == indentation) {
      if (reader.line.key == Object::EXECUTORS) {
        if (!ExecutorManagerParser::parse(reader,
                                          configManager.executorManager,
                                          indentation + 1)) {
          return;
        }
      } else {
        reader.error = "Unrecognized base entry";
        return;
      }
    }
  }

public:

  template <typename Stream>
  bool parse(Stream & stream, ConfigManager & configManager) {
    int indentation = 0;

    StreamReader<Stream> reader(stream);
    parseBaseConfig(reader, configManager);

    if (!reader.error.empty()) {
      mfl::out::println(stderr, "Failed to parse config at line: {:d}", reader.lineNumber);
      mfl::out::println(stderr, "  Error: {:s}", reader.error);
      mfl::out::println(stderr, "  Key: {:s}", reader.line.key);
      if (!reader.line.value.empty()) {
        mfl::out::println(stderr, "  Value: {:s}", reader.line.value);
      }
      return false;
    }

    return true;
  }
};
