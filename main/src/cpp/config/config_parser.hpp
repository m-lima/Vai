#pragma once

#include <rapidjson/reader.h>

class ConfigParser {
private:
  struct Key {
    static constexpr auto EXECUTOR = "executor";
  };

  enum State {
    START,
    EXECUTOR
  };

  State mState = State::START;
  void * mParser;

public:
  ConfigParser() : mParser(this) {}

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
  bool Null() { return false; }
  bool String(const char *, rapidjson::SizeType, bool) { return false; }

  // Source types
  bool StartObject() {
    return mState == State::START;
  }

  bool EndObject(rapidjson::SizeType memberCount) {
    mParser = 0;
    return mState != State::START;
  }

  bool Key(const char * str, rapidjson::SizeType length, bool copy) {
    if (!strcmp(str, Key::EXECUTOR)) {
      mState = State::EXECUTOR;
      return true;
    }

    return false;
  }

};
