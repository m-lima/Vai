#pragma once

#include <string>

#include "../config/config_manager.hpp"

class Console {
private:
  ConfigManager mConfigManager;

public:
  Console(int argc, char * argv[]);
  int start();
};

