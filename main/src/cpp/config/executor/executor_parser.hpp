#pragma once

#include <rapidjson/reader.h>

#include "executor.hpp"

class ExecutorParser {
private:

  struct Key {
    static constexpr auto NAME = "name";
    static constexpr auto COMMAND = "command";
    static constexpr auto PARSER = "parser";
    static constexpr auto VALIDATOR = "validator";
  };

  enum State {
    START,
    NAME,
    COMMAND,
    PARSER,
    VALIDATOR
  };

  State mState = START;
  Executor mExecutor;

public:
  // Invalid types
  bool Bool(bool) { return false; }
  bool Int(int) { return false; }
  bool Uint(unsigned) { return false; }
  bool Int64(int64_t) { return false; }
  bool Uint64(uint64_t) { return false; }
  bool Double(double) { return false; }
  bool RawNumber(const char *, rapidjson::SizeType, bool) { return false; }
  bool StartArray() { return false; }
  bool EndArray(rapidjson::SizeType) { return false; }

  // Source types
  bool StartObject();
  bool EndObject(rapidjson::SizeType memberCount);
  bool Key(const char * str, rapidjson::SizeType length, bool copy);
  bool Null();
  bool String(const char * str, rapidjson::SizeType length, bool copy);

  inline Executor getExecutor() const {
    return Executor(mExecutor);
  }
};
