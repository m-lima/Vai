#pragma once

#include <vector>

#include "config_model.hpp"
#include "executor/executor_manager.hpp"

class ConfigManager {
private:
  const std::string cConfigFile;

  void loadExecutors();

public:
  ConfigManager();

  void load();
  void save();

  ExecutorManager executorManager;
};

