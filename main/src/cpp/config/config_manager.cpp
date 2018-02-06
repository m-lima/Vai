#include "config_manager.hpp"

#include <iostream>
#include <fstream>

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

ConfigManager::ConfigManager(const std::string & configFolder) : cConfigFolder(getDefaultConfigFolder(configFolder)) {
  load();
}

void ConfigManager::load() {
  loadExecutors();
}

void ConfigManager::loadExecutors() {
//  std::string configFile = cConfigFolder + "executors.cfg";
//
//  std::ifstream fileStream(configFile);
//  if (!fileStream.is_open()) {
//    return;
//  }
//
//  nlohmann::json config;
//
//  fileStream >> config;
//
//  mConfig.executors.clear();
//
////  auto executors = config[ConfigFormat::Executors::Field];
////  for (auto & executor : executors) {
////    mConfig.executors.push_back(executor.get<Executor>());
////  }
//
////  mConfig.executors = std::vector<Executor>{config[ConfigFormat::Executors::Field].begin(),
////                                            config[ConfigFormat::Executors::Field].end()};
//
//  mConfig.executors = config.at(ConfigFormat::Executors::Field).get<std::vector<Executor>>();
};

void ConfigManager::save(const Config & config) {
//  nlohmann::json saver;
//  saver[ConfigFormat::Executors::Field] = config.executors;
//  std::cout << saver <<std::endl;
}

