#pragma once

#include <string>
#include <sstream>

#include <mfl/out.hpp>

#include "config_manager.hpp"
#include "executor/executor_parser.hpp"

class ConfigParser {
private:
//  enum LineType {
//    EXPECTED_INDENTATION,
//    LESS_INDENTATION,
//    MORE_INDENTATION,
//    EMPTY,
//    COMMENT
//  };

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
    int lineNumber;
    std::string error;

    StreamReader(Stream && stream) : mStream(std::move(stream)) {}

    bool readNext() {
      std::string buffer;
      while (std::getline(mStream, buffer)) {
        lineNumber++;
        line = buffer;

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

//  // TODO: This is executed twice for lines where do-while is used
//  // TODO: Currently, we required an empty line at the end of the file
//  LineType getLineType(const std::string & line, int expectedIndentation) {
//    int indentation = 0;
//    for (int i = 0; i < line.size(); ++i) {
//      if (!std::isspace(line[i])) {
//        if (line[i] == '#') {
//          return COMMENT;
//        }
//        indentation = i;
//        break;
//      }
//    }
//
//    if (indentation == line.size()) {
//      return EMPTY;
//    }
//
//    if (indentation > expectedIndentation) return MORE_INDENTATION;
//    if (indentation < expectedIndentation) return LESS_INDENTATION;
//    return EXPECTED_INDENTATION;
//
//  }

  template <typename Stream>
  bool parseExecutor(StreamReader<Stream> & reader,
                     ExecutorManager & executorManager,
                     int indentation) {
    ExecutorParser executorParser;

    while (reader.readNext()) {
      if (reader.line.indentation < 0) {
        continue;
      }

      if (reader.line.indentation > indentation) {
        reader.error = fmt::format("Wrong indentation. Was expecting {:d} and got {:d}",
                                   indentation,
                                   reader.line.indentation);
        return false;
      }

      if (reader.line.indentation < indentation) {
        break;
      }

      executorParser.parse(reader.line.value);
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

    while (reader.readNext()) {
      if (reader.line.indentation < 0) {
        continue;
      }

      if (reader.line.indentation > indentation) {
        reader.error = fmt::format("Wrong indentation. Was expecting {:d} and got {:d}",
                                   indentation,
                                   reader.line.indentation);
        return false;
      }

      if (reader.line.indentation < indentation) {
        break;
      }

      if (reader.line.value == Object::EXECUTOR) {
        if (!parseExecutor(reader, executorManager, indentation + 1)) {
          return false;
        }
      }
    }

    configManager.executorManager = executorManager;
    return true;
  }


public:

  template<typename Stream>
  bool parse(Stream & stream, ConfigManager & configManager) {
    int indentation = 0;

    StreamReader<Stream> reader(stream);
    while (reader.readNext()) {
      if (reader.line.indentation < 0) {
        continue;
      }

      if (reader.line.indentation > indentation) {
        reader.error = fmt::format("Wrong indentation. Was expecting {:d} and got {:d}",
                                   indentation,
                                   reader.line.indentation);
        break;
      }

      if (reader.line.value == Object::EXECUTORS) {
        if (!parseExecutors(reader, configManager, indentation + 1)) {
          break;
        }
      }
    }

    mfl::out::println(stderr, "Failed to parse config at line: {:d}", reader.lineNumber);
    if (!reader.error.empty()) {
      mfl::out::println(stderr, "Error: {:s}", reader.error);
    }
    return false;

//    std::string line;
//    while (std::getline(stream, line)) {
//      mLineNumber++;
//
//      switch (getLineType(line, indentation)) {
//        case COMMENT: continue;
//        case EMPTY: continue;
//        default: return false;
//        case EXPECTED_INDENTATION:
//          mfl::string::trimInPlace(line);
//
//          if (line == Object::EXECUTORS) {
//            return parseExecutors(stream, configManager);
//          }
//      }
//    }
  }
};
