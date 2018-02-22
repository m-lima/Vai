#pragma once

#include <rapidjson/rapidjson.h>
#include <rapidjson/encodings.h>
#include <rapidjson/reader.h>

#include "executor.hpp"

#ifdef VERBOSE
#include <mfl/out.hpp>
#endif

enum State {
    START,
    NAME,
    COMMAND,
    PARSER,
    VALIDATOR
};

class ExecutorParser
    : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, ExecutorParser> {

private:
    static constexpr auto NAME = "name";
    static constexpr auto COMMAND = "command";
    static constexpr auto PARSER = "parser";
    static constexpr auto VALIDATOR = "validator";

    State mState = State::START;
    Executor mExecutor;

public:
    bool StartObject() {
      return mState == State::START;
    }

    bool EndObject(rapidjson::SizeType memberCount) {
      return mState != State::START;
    }

    bool Default() {
      return false;
    }

    inline Executor getExecutor() const {
      return mExecutor;
    }

    bool Key(const char* str, rapidjson::SizeType length, bool copy);
    bool Null();
    bool String(const char* value, rapidjson::SizeType length, bool copy);
};
