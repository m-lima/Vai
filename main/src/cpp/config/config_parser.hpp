#pragma once

#include <rapidjson/reader.h>
#include "executor/executor_manager.hpp"

class ConfigParser {
private:

  struct Key {
    static constexpr auto EXECUTORS = "executors";
    static constexpr auto NAME = "name";
    static constexpr auto COMMAND = "command";
    static constexpr auto PARSER = "parser";
    static constexpr auto VALIDATOR = "validator";
  };

  enum State {
    START,
    END
  };

  struct ParsingState {
    char * target;
    State state;
  } mParsingState;

  ExecutorManager * pExecutorManager;
  Executor mExecutor;

public:
  ConfigParser(ExecutorManager & executorManager)
      : pExecutorManager(&executorManager) {}
  // Invalid types
  bool Bool(bool) { return false; }
  bool Int(int) { return false; }
  bool Uint(unsigned) { return false; }
  bool Int64(int64_t) { return false; }
  bool Uint64(uint64_t) { return false; }
  bool Double(double) { return false; }
  bool RawNumber(const char *, rapidjson::SizeType, bool) { return false; }
  bool Null() { return false; }
  bool String(const char *, rapidjson::SizeType, bool) { return false; }

  // Source types
  bool StartObject();
  bool EndObject(rapidjson::SizeType memberCount);
  bool Key(const char * str, rapidjson::SizeType length, bool copy);
  bool StartArray();
  bool EndArray(rapidjson::SizeType);

};
