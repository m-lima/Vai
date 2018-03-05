#include "config_manager.hpp"

#include <iostream>
#include <fstream>

#include <mfl/path.hpp>
#include <mfl/exception.hpp>

#ifdef VERBOSE
#include <mfl/out.hpp>
#endif

#include "config_parser.hpp"

namespace {
  std::string getDefaultConfigFile() {
    return mfl::path::getConfigPath() + "/vai/config";
  }
}

ConfigManager::ConfigManager()
    : cConfigFile(getDefaultConfigFile()) {
#ifdef VERBOSE
  mfl::out::println("ConfigManager::ctor cConfigFile = {:s}", cConfigFile);
#endif
  load();
}

void ConfigManager::load() {
  std::ifstream fileStream(cConfigFile);
  if (!ConfigParser::parse(fileStream, *this)) {
    throw mfl::Exception("Failed to load config. Aborting");
  }

#ifdef VERBOSE
  std::string json((std::istreambuf_iterator<char>(fileStream)),
                   (std::istreambuf_iterator<char>()));
  mfl::out::println("ConfigManager::load executors:\n{:s}", json);
  for (auto & executor : executorManager.executors) {
    mfl::out::println("  Name: {}", executor.getName());
    mfl::out::println("  Command: {}", executor.getCommand());
    mfl::out::println("  Parser: {}", executor.getParser());
    mfl::out::println("  Validator: {}", executor.getValidator());
  }
#endif
}

void ConfigManager::save() const {
  std::ofstream fileStream(cConfigFile + ".save");
  ConfigParser::save(fileStream, *this);
}

