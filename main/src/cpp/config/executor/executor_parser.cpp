#include "executor_parser.hpp"

#include <regex>

namespace {
  struct Key {
    static constexpr auto NAME = "name";
    static constexpr auto COMMAND = "command";
    static constexpr auto PARSER = "parser";
    static constexpr auto VALIDATOR = "validator";
  };

  const std::regex REGEX("^(name|command|parser|validator)"
                             ":[[:space:]]*"
                             "(.+)$");
//  const std::regex REGEX("^[[:space:]]*"
//                             "(name|command|parser|validator)"
//                             "[[:space:]]*:[[:space:]]*"
//                             "(.+)"
//                             "[[:space:]]*$");
}

bool ExecutorParser::parse(const std::string & value) {
  std::smatch match;
  if (!std::regex_match(value, match, REGEX)) {
    return false;
  }

  if (match[1] == Key::NAME) {
    executor.setName(match[2]);
    return true;
  } else if (match[1] == Key::COMMAND) {
    executor.setCommand(match[2]);
    return true;
  } else if (match[1] == Key::PARSER) {
    executor.setParser(match[2]);
    return true;
  } else if (match[1] == Key::VALIDATOR) {
    executor.setValidator(match[2]);
    return true;
  }

  return false;
}
