#pragma once

#include <string>
#include <vector>
#include <functional>
#include <regex>

#include "parser/abstract_parser.hpp"

class Executor {
private:
  const std::string cName;
  const std::string cCommand;
  const std::regex cValidator;
  const AbstractParser cParser;

public:
  Executor(const std::string & name,
           const std::string & command,
           const AbstractParser & parser,
           const std::string & validator = ".*")
      : cName(name),
        cCommand(command),
        cParser(parser),
        cValidator(validator) {}

  std::string getName() {
    return cName;
  }

  std::string getCommand() {
    return cCommand;
  }

  bool validateEntry(const std::string & entry) {
    return std::regex_search(entry.cbegin(), entry.cend(), cValidator);
  }

  std::string getExecutorCommand(const std::string & entry) {
    static std::regex ENTRY_REPLACER("##ENTRY##");
    return std::regex_replace(cCommand, ENTRY_REPLACER, entry);
  }

  std::vector<std::string> parseSuggestions(const std::string & body) {
    return cParser(body);
  }
};
