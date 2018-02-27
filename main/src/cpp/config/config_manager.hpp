#pragma once

#include <vector>

#include "executor/executor_manager.hpp"

class ConfigManager {
private:
  const std::string cConfigFile;

  void loadExecutors();

public:
  ConfigManager();

  void load();
  void save() const;

  ExecutorManager executorManager;
};

