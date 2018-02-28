#include "executor_parser.hpp"

namespace {
  struct Key {
    static constexpr auto NAME = "name";
    static constexpr auto COMMAND = "command";
    static constexpr auto COMPLETER = "completer";
    static constexpr auto VALIDATOR = "validator";
  };
}

bool ExecutorParser::parse(const std::string & key,
                           const std::string & value) {
  if (key == Key::NAME) {
    executor->setName(value);
    return true;
  } else if (key == Key::COMMAND) {
    executor->setCommand(value);
    return true;
  } else if (key == Key::COMPLETER) {
    executor->setCompleter(value);
    return true;
  } else if (key == Key::VALIDATOR) {
    executor->setValidator(value);
    return true;
  }

  return false;
}
