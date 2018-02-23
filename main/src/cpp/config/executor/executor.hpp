#pragma once

#include <string>
#include <regex>

#include <mfl/string.hpp>

#include "parser/abstract_parser.hpp"
#include "parser/dumb_parser.hpp"
#include "parser/parser_registry.hpp"

class Executor {
private:
  std::string mName;
  std::string mCommand;
  AbstractParser mParser;
  std::regex mValidator;
  std::string mValidatorString;

public:
  Executor() : mParser(DumbParser()) {}

  Executor(const std::string & name,
           const std::string & command,
           const AbstractParser & parser,
           const std::string & validator = ".*")
      : mName(mfl::string::toLower(name)),
        mCommand(command),
        mParser(parser),
        mValidator(validator),
        mValidatorString(validator) {}

  void clear() {
    mName = "";
    mCommand = "";
    mParser = ParserRegistry::getParserByName("DUMB");
    mValidator = ".*";
    mValidatorString = ".*";
  }

  std::string getName() const {
    return mName;
  }

  void setName(const std::string & name) {
    mName = mfl::string::toLower(name);
  }

  std::string getCommand() const {
    return mCommand;
  }

  void setCommand(const std::string & command) {
    mCommand = command;
  }

  std::string getParser() const {
    return mParser.getName();
  }

  void setParser(const std::string & parser) {
    mParser = ParserRegistry::getParserByName(parser);
  }

  std::string getValidator() const {
    return mValidatorString;
  }

  void setValidator(const std::string & validator) {
    mValidatorString = validator;
    mValidator = std::regex(validator);
  }

  bool validateEntry(const std::string & entry) {
    return std::regex_search(entry.cbegin(), entry.cend(), mValidator);
  }

  std::string getExecutorCommand(const std::string & entry) {
    static const std::regex ENTRY_REPLACER("##ENTRY##");
    return std::regex_replace(mCommand, ENTRY_REPLACER, entry);
  }

  std::vector<std::string> parseSuggestions(const std::string & body) {
    return mParser(body);
  }
};
