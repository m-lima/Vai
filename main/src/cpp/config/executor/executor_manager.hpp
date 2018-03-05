#pragma once

#include <algorithm>
#include <string>
#include <vector>

#include <mfl/string.hpp>

#include "executor.hpp"

class ExecutorManager {
public:
  std::vector<Executor> executors;

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

  inline std::vector<std::string> complete(const std::string & name,
                                           const std::string & command) const {
    const auto lowerName = mfl::string::toLower(name);
    auto executor = std::find_if(executors.begin(),
                                 executors.end(),
                                 [&lowerName](const Executor & executor) -> bool {
                                   return executor.getName() == lowerName;
                                 });

    if (executor == executors.end()) {
      return {};
    }

    return executor->complete(command);
  }

  inline std::vector<std::string> getPossibleExecutors(const std::string & name) const {
    std::string lowerName = mfl::string::toLower(name);
    std::vector<std::string> possible;

    for (const auto & executor : executors) {
      if (!executor.getName().compare(0, lowerName.size(), lowerName)) {
        possible.emplace_back(executor.getName());
      }
    }

    return possible;
  }
};

