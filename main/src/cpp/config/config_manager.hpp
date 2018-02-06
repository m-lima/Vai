#pragma once

#include <vector>

#include "config_model.hpp"

class ConfigManager {
private:
  const std::string cConfigFolder;
  Config mConfig;

  void loadExecutors();

public:
  ConfigManager(const std::string & configFolder = "");

  void load();
  void save(const Config & config);
};

