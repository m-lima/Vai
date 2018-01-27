#pragma once

#include <string>
#include <regex>

class Executor {
  private:
    const std::string cName;
    const std::string cCommand;
    const std::regex cValidator;

  public:
    Executor(const std::string & name,
             const std::string & command,
             const std::string & validator = ".*")
      : cName(name),
        cCommand(command),
        cValidator(validator)
    {}

    std::string getName() {
      return cName;
    }

    std::string getCommand() {
      return cCommand;
    }

    bool validateEntry(const std::string & entry) {
      return false;
    }

};
