#pragma once

#include <string>

class Console {
public:
  int start(const std::string & configFolder, const std::string & executor = "", const std::string & command = "");
};
