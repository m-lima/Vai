#include "config_manager.hpp"

#include <mfl/file.hpp>
#include <iostream>

#include "config_format.hpp"
#include "../parser/parser_registry.hpp"

namespace {
  std::string getDefaultConfigFolder(const std::string & configFolder) {
    if (configFolder.empty()) {
      return ".config/vai/";
    }

    std::string safeConfigFolder(configFolder);

    if (safeConfigFolder[safeConfigFolder.length() - 1] != '/') {
      safeConfigFolder += '/';
    }
    return safeConfigFolder;
  }
}

ConfigManager::ConfigManager(const std::string & configFolder) : cConfigFolder(getDefaultConfigFolder(configFolder)) {}

void ConfigManager::loadKnownExecutorNames() {
  std::string configFile = cConfigFolder + "executors.cfg";

  std::ifstream fileStream(configFile);
  if (!fileStream.is_open()) {
    return;
  }

  fileStream >> mExecutorConfig;
}

std::vector<std::string> ConfigManager::getExecutorNames() {
  loadKnownExecutorNames();

  auto executors = mExecutorConfig[ConfigFormat::Executors::Field];
  std::vector<std::string> executorNames;

  for (auto & executor : executors) {
    executorNames.push_back(executor[ConfigFormat::Executors::name]);
  }

  return executorNames;
}

Executor ConfigManager::loadExecutorByName(const std::string & executorName) {
  auto executors = mExecutorConfig[ConfigFormat::Executors::Field];

  for (auto & executor : executors) {
    if (executor[ConfigFormat::Executors::name] == executorName) {
      return Executor(executor[ConfigFormat::Executors::name],
                      executor[ConfigFormat::Executors::command],
                      ParserRegistry::getParserByName(executor[ConfigFormat::Executors::parser]),
                      executor[ConfigFormat::Executors::validator]);
    }
  }
}

void ConfigManager::saveExecutor(const std::string & name, const Executor & executor) {
  // TODO save json
}
