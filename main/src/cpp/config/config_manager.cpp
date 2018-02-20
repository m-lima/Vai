#include "config_manager.hpp"

#include <iostream>
#include <fstream>

#include <mfl/path.hpp>

#ifdef VERBOSE
  #include <mfl/out.hpp>
#endif

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
  if (!fileStream.is_open()) {
#ifdef VERBOSE
    mfl::out::println("ConfigManager::load Failed to open file {:s}", cConfigFile);
#endif
    return;
  }

  nlohmann::json config;
  fileStream >> config;

  executorManager.executors =
      config.at(ConfigFormat::Executors::Field).get<std::vector<Executor>>();

#ifdef VERBOSE
  mfl::out::println("ConfigManager::load executors = {}", config);
#endif
}

void ConfigManager::save() {
  nlohmann::json saver;
  saver[ConfigFormat::Executors::Field] = executorManager.executors;
  std::cout << saver << std::endl;
}

