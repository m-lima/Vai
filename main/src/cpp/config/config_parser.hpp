#pragma once

#include <string>
#include <sstream>

#include <mfl/out.hpp>

#include "config_manager.hpp"
#include "executor/executor_parser.hpp"

class ConfigParser {
private:
  enum Type {
    OBJECT,
    COMMENT,
    KEY
  };

  struct Object {
    static constexpr auto EXECUTORS = "-executors";
  };

  static Type getType(const std::string & line) {
    char c = 0;
    for (char i : line) {
      c = i;
      switch (c) {
        case ' ': continue;
        case '#': return COMMENT;
        case '-': return OBJECT;
        default: return KEY;
      }
    }
  }

  static bool isIndentationValid(const std::string & line,
                                 int expectedIndentation) {
    for (int i = 0; i < expectedIndentation && i < line.size(); ++i) {
      if (!std::isspace(line[i])) {
        return false;
      }
    }

    return true;
  }

  template<typename Stream>
  static bool parseExecutor(Stream & stream,
                            ExecutorManager & executorManager,
                            int indentation,
                            int * lineNumber) {
    ExecutorParser executorParser;

    std::string line;
    while (std::getline(stream, line)) {

      if (!isIndentationValid(line, indentation)) {
        break;
      }

      mfl::string::trimInPlace(line);

      if (line.empty()) {
        if (executorParser.isValid()) {
          executorManager.executors.push_back(executorParser.executor);
          return true;
        }

        break;
      }
    }

    // TODO Move to parent function
    mfl::out::println(stderr, "Failed to parse config at line: {:d}", *lineNumber);
    return false;
  }

  template<typename Stream>
  static bool parseExecutors(Stream & stream,
                             ConfigManager & configManager,
                             int indentation,
                             int * lineNumber) {
    std::string line;
    while (std::getline(stream, line)) {

      if (!isIndentationValid(line, indentation)) {
        break;
      }

      mfl::string::trimInPlace(line);
    }

    return false;
  }

public:

  template<typename Stream>
  static bool parse(Stream & stream, ConfigManager & configManager) {
    ExecutorManager executorManager;
    ExecutorParser executorParser;

    std::string line;
    while (std::getline(stream, line)) {

      mfl::string::trimInPlace(line);

      switch (line[0]) {
        case 0:
        case '#': continue;
        case '-':
          if (line == Object::EXECUTORS) {
            if (!executorManager.executors.empty()) {
              return false;
            }
            executorManager = ExecutorManager();
          }

          if (line == "-executor") {
            executorParser = ExecutorParser();
          }

          break;
        default: executorParser.parse(line);
      }
    }

    if (executorParser.isValid()) {
      executorManager.executors.push_back(executorParser.executor);
    }

    configManager.executorManager = std::move(executorManager);
  }
};
