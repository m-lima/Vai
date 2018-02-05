#pragma once

#include <vector>
#include <fstream>

#include <nlohmann/json.hpp>

#include "../executor/executor.hpp"

class ConfigManager {
private:
  const std::string cConfigFolder;
  nlohmann::json mExecutorConfig;

  void loadKnownExecutorNames();

public:
  ConfigManager(const std::string & configFolder = "");

  std::vector<std::string> getExecutorNames();
  Executor loadExecutorByName(const std::string & executor);
  void saveExecutor(const std::string & name, const Executor & executor);
};
