#pragma once

#include <algorithm>

#include <mfl/string.hpp>

#include "executor.hpp"

struct Execution {
  const bool status;
  const std::string command;
};

class ExecutorManager {
public:

  Execution getExecution(const std::string & name, const std::string & command) {
    const auto lowerName = mfl::string::toLower(name);
    auto executor = std::find_if(executors.begin(),
                                 executors.end(),
                                 [&lowerName](const Executor & executor) -> bool {
                                   return executor.getName() == lowerName;
                                 });

    return executor == executors.end()
           ? Execution{false, ""}
           : Execution{true, executor->getExecutorCommand(command)};
  }

  std::vector<Executor> executors;
};

