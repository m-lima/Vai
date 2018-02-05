#pragma once

#include <vector>
#include <string>

#include "executor.hpp"
#include "../config/config_manager.hpp"

class ExecutorStore {
private:
  const ConfigManager cConfigManager;
public:
  ExecutorStore(const ConfigManager & configManager);
  std::vector<std::string> getPossibleExecutors(const std::string & executor);
  const Executor & getExecutor(const std::string & executor) const;
};