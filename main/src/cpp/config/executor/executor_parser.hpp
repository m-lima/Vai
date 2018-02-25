#pragma once

#include <string>

#include "executor.hpp"

class ExecutorParser {
public:
  Executor executor;

  bool parse(const std::string & value);
  bool isValid() const {
    return !executor.getName().empty()
           && !executor.getCommand().empty();
  }
};
