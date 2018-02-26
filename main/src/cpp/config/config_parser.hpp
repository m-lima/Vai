#pragma once

#include <string>
#include <sstream>

#include <mfl/out.hpp>

#include "config_manager.hpp"
#include "executor/executor_parser.hpp"

class ConfigParser {
private:

  struct Line {
    int indentation = -1;
    std::string value = "";

    Line() = default;

    Line & operator=(const std::string & rawLine) noexcept {
      int currentIndentation = 0;
      for (int i = 0; i < rawLine.size(); ++i) {
        if (!std::isspace(rawLine[i])) {
          if (rawLine[i] == '#') {
            indentation = -1;
            value = "";
            return *this;
          }
          currentIndentation = i;
          break;
        }
      }

      if (currentIndentation == rawLine.size()) {
        indentation = -1;
        value = "";
        return *this;
      }

      indentation = currentIndentation;
      value = mfl::string::trim(rawLine);
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

        if (line.indentation > expectedIndentation) {
          error = fmt::format("Wrong indentation. Was expecting {:d} and got {:d}",
                              expectedIndentation,
                              line.indentation);
          return false;
        }

        if (line.indentation >= 0) {
          return true;
        }
      }

      return false;
    }

  };

  struct Object {
    static constexpr auto EXECUTORS = "executors";
    static constexpr auto EXECUTOR = "executor";
  };

  template <typename Stream>
  bool parseExecutor(StreamReader<Stream> & reader,
                     ExecutorManager & executorManager,
                     int indentation) {
    ExecutorParser executorParser;

    while (reader.readNext(indentation)) {
      if (reader.line.indentation < indentation) {
        break;
      }

      if (!executorParser.parse(reader.line.value)) {
        reader.error = "Failure parsing executor";
        return false;
      }
    }

    if (executorParser.isValid()) {
      executorManager.executors.push_back(executorParser.executor);
      return true;
    }

    reader.error = "Invalid executor object";
    return false;
  }

  template <typename Stream>
  bool parseExecutors(StreamReader<Stream> & reader,
                      ConfigManager & configManager,
                      int indentation) {
    ExecutorManager executorManager;

    if (!reader.readNext(indentation)) {
      return false;
    }

    while (reader.line.indentation == indentation) {
      if (reader.line.value == Object::EXECUTOR) {
        if (!parseExecutor(reader, executorManager, indentation + 1)) {
          return false;
        }
      } else {
        reader.error = "Unrecognized entry";
        return false;
      }
    }

    if (reader.error.empty()) {
      configManager.executorManager = executorManager;
      return true;
    }
    return false;
  }

  template <typename Stream>
  void parseBaseConfig(StreamReader<Stream> & reader,
                       ConfigManager & configManager) {
    int indentation = 0;

    if (!reader.readNext(indentation)) {
      return;
    }

    while (reader.line.indentation == indentation) {
      if (reader.line.value == Object::EXECUTORS) {
        if (!parseExecutors(reader, configManager, indentation + 1)) {
          return;
        }
      } else {
        reader.error = "Unrecognized entry";
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
      mfl::out::println(stderr, "  Line: {:s}", reader.line.value);
      return false;
    }

    return true;
  }
};
