#include "executor_parser.hpp"

bool ExecutorParser::StartObject() {
  if (mState == State::START) {
    mExecutor = Executor();
    return true;
  }

  return false;
}

bool ExecutorParser::EndObject(rapidjson::SizeType memberCount) {
  return mState != State::START;
}

bool ExecutorParser::Key(const char * str, rapidjson::SizeType length, bool copy) {
  if (length == 0) {
    return false;
  }

  if (!strcmp(str, Key::NAME)) {
    mState = State::NAME;
    return true;
  }

  if (!strcmp(str, Key::COMMAND)) {
    mState = State::COMMAND;
    return true;
  }

  if (!strcmp(str, Key::PARSER)) {
    mState = State::PARSER;
    return true;
  }

  if (!strcmp(str, Key::VALIDATOR)) {
    mState = State::VALIDATOR;
    return true;
  }

  return false;
}

bool ExecutorParser::Null() {
  switch (mState) {
    case State::NAME:
      mExecutor.setName();
      return true;
    case State::COMMAND:
      mExecutor.setCommand();
      return true;
    case State::PARSER:
      mExecutor.setParser();
      return true;
    case State::VALIDATOR:
      mExecutor.setValidator();
      return true;
    default:
      return false;
  }
}

bool ExecutorParser::String(const char * str, rapidjson::SizeType length, bool copy) {
  if (length == 0) {
    return false;
  }

  switch (mState) {
    case State::NAME:
      mExecutor.setName(str);
      return true;
    case State::COMMAND:
      mExecutor.setCommand(str);
      return true;
    case State::PARSER:
      mExecutor.setParser(str);
      return true;
    case State::VALIDATOR:
      mExecutor.setValidator(str);
      return true;
    default:
      return false;
  }
}
