#pragma once

#include <string>
#include <regex>

#include <mfl/string.hpp>

#include "completer/abstract_completer.hpp"
#include "completer/dumb_completer.hpp"
#include "completer/completer_registry.hpp"

class Executor {
private:
  std::string mName;
  std::string mCommand;
  const AbstractCompleter * mCompleter;
  std::regex mValidator;
  std::string mValidatorString;

public:
  Executor() : Executor("", "", CompleterRegistry::getCompleterByName("DUMB")) {}

  Executor(const std::string & name,
           const std::string & command,
           const AbstractCompleter * completer,
           const std::string & validator = ".*")
      : mName(mfl::string::toLower(name)),
        mCommand(command),
        mCompleter(completer),
        mValidator(validator),
        mValidatorString(validator) {}

  std::string getName() const {
    return mName;
  }

  void setName(const std::string & name = "") {
    mName = mfl::string::toLower(name);
  }

  std::string getCommand() const {
    return mCommand;
  }

  void setCommand(const std::string & command = "") {
    mCommand = command;
  }

  std::string getCompleter() const {
    return mCompleter->getName();
  }

  void setCompleter(const std::string & completer = "DUMB") {
    mCompleter = CompleterRegistry::getCompleterByName(completer);
  }

  std::string getValidator() const {
    return mValidatorString;
  }

  void setValidator(const std::string & validator = ".*") {
    mValidatorString = validator;
    mValidator = std::regex(validator);
  }

  bool validateEntry(const std::string & entry) const {
    return std::regex_match(entry.cbegin(), entry.cend(), mValidator);
  }

  int execute(const std::string &) const;

  std::vector<std::string> complete(const std::string &) const;

  template <int Offset>
  static std::string concatenateCommand(int argc, char * argv[]) {
    if (argc < Offset + 3) {
      return "";
    }

    if (argc == Offset + 3) {
      return argv[Offset + 2];
    }

    std::string command = argv[Offset + 2];

    for (int i = Offset + 3; i < argc; ++i) {
      command = command + " " + argv[i];
    }

    return command;
  }
};
