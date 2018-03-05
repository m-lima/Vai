#pragma once

#include <algorithm>

#include <mfl/string.hpp>

#include "executor.hpp"

class ExecutorManager {
public:
  inline int execute(const std::string & name, const std::string & command) const {
    const auto lowerName = mfl::string::toLower(name);
    auto executor = std::find_if(executors.begin(),
                                 executors.end(),
                                 [&lowerName](const Executor & executor) -> bool {
                                   return executor.getName() == lowerName;
                                 });

    if (executor == executors.end()) {
      return -1;
    }

    return executor->execute(command);
  }

  std::vector<Executor> executors;
};

