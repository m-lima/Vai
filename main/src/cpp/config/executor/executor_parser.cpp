#include "executor_parser.hpp"

bool ExecutorParser::StartObject() {
  return mState == State::START;
}

bool ExecutorParser::EndObject(rapidjson::SizeType memberCount) {
  return mState != State::START;
}

bool ExecutorParser::Key(const char * str, rapidjson::SizeType length, bool copy) {
  if (length == 0) {
    return false;
  }

  if (!strcmp(str, NAME)) {
    mState = State::NAME;
    return true;
  }

  if (!strcmp(str, COMMAND)) {
    mState = State::COMMAND;
    return true;
  }

  if (!strcmp(str, PARSER)) {
    mState = State::PARSER;
    return true;
  }

  if (!strcmp(str, VALIDATOR)) {
    mState = State::VALIDATOR;
    return true;
  }

  return false;
}

bool ExecutorParser::Null() {
  switch (mState) {
    case State::NAME:
      mExecutor.setName("");
      return true;
    case State::COMMAND:
      mExecutor.setCommand("");
      return true;
    case State::PARSER:
      mExecutor.setParser("");
      return true;
    case State::VALIDATOR:
      mExecutor.setValidator("");
      return true;
    default:
      return false;
  }
}

bool ExecutorParser::String(const char * value, rapidjson::SizeType length, bool copy) {
  if (length == 0) {
    return false;
  }

  switch (mState) {
    case State::NAME:
      mExecutor.setName(value);
      return true;
    case State::COMMAND:
      mExecutor.setCommand(value);
      return true;
    case State::PARSER:
      mExecutor.setParser(value);
      return true;
    case State::VALIDATOR:
      mExecutor.setValidator(value);
      return true;
    default:
      return false;
  }
}
