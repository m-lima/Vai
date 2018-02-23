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

  void * getParser() {
    return mParser;
  }
};
