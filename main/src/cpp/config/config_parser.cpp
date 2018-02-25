#include "config_parser.hpp"

bool ConfigParser::StartObject() {
  if (mParsingState.target == Target::SELF) {
    pExecutorManager->executors.clear();
    return true;
  }

  return false;
}

bool ConfigParser::EndObject(rapidjson::SizeType memberCount) {
  if (mParsingState.target == Target::SELF) {
    return true;
  }
}

bool ConfigParser::Key(const char * str, rapidjson::SizeType length, bool copy) {
  if (!strcmp(str, Key::EXECUTORS)) {
    mParsingState = { .target = Target::EXECUTOR_MANAGER, .state = State::START };
    return true;
  }

  return false;
}

bool ConfigParser::StartArray() {
  return false;
}

bool ConfigParser::EndArray(rapidjson::SizeType) {
  return false;
}

