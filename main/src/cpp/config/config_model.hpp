#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "executor/executor.hpp"
#include "executor/parser/parser_registry.hpp"

#define CONFIG_FORMAT_EXECUTORS_FIELD "executors"
#define CONFIG_FORMAT_EXECUTORS_NAME "name"
#define CONFIG_FORMAT_EXECUTORS_COMMAND "command"
#define CONFIG_FORMAT_EXECUTORS_PARSER "parser"
#define CONFIG_FORMAT_EXECUTORS_VALIDATOR "validator"

struct ConfigFormat {
  struct Executors {
    static constexpr auto Field = CONFIG_FORMAT_EXECUTORS_FIELD;

    static constexpr auto name = CONFIG_FORMAT_EXECUTORS_NAME;
    static constexpr auto command = CONFIG_FORMAT_EXECUTORS_COMMAND;
    static constexpr auto parser = CONFIG_FORMAT_EXECUTORS_PARSER;
    static constexpr auto validator = CONFIG_FORMAT_EXECUTORS_VALIDATOR;
  };
};

struct Config {
  std::vector<Executor> executors;
};

static void to_json(nlohmann::json & json, const Executor & executor) {
  json = nlohmann::json{{CONFIG_FORMAT_EXECUTORS_NAME,      executor.getName()},
                        {CONFIG_FORMAT_EXECUTORS_COMMAND,   executor.getCommand()},
                        {CONFIG_FORMAT_EXECUTORS_PARSER,    executor.getParser()},
                        {CONFIG_FORMAT_EXECUTORS_VALIDATOR, executor.getValidator()}};
}

static void from_json(const nlohmann::json & json, Executor & executor) {
  executor = Executor(json.at(CONFIG_FORMAT_EXECUTORS_NAME).get<std::string>(),
                      json.at(CONFIG_FORMAT_EXECUTORS_COMMAND).get<std::string>(),
                      ParserRegistry::getParserByName(json.at(CONFIG_FORMAT_EXECUTORS_PARSER).get<std::string>()),
                      json.at(CONFIG_FORMAT_EXECUTORS_VALIDATOR).get<std::string>());
}

#undef CONFIG_FORMAT_EXECUTORS_FIELD
#undef CONFIG_FORMAT_EXECUTORS_NAME
#undef CONFIG_FORMAT_EXECUTORS_COMMAND
#undef CONFIG_FORMAT_EXECUTORS_PARSER
#undef CONFIG_FORMAT_EXECUTORS_VALIDATOR
