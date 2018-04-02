#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <optional>

#include <mfl/string.hpp>

#include "executor.hpp"

class ExecutorManager {
public:
  std::vector<Executor> executors;

  inline std::optional<Executor> getExecutorByName(const std::string & name) const {
    if (name.empty()) {
      return {};
    }

    const auto lowerName = mfl::string::toLower(name);
    auto executor = std::find_if(executors.begin(),
                                 executors.end(),
                                 [&lowerName](const Executor & executor) -> bool {
                                   return executor.getName() == lowerName;
                                 });

    if (executor == executors.end()) {
      return {};
    }

    return std::make_optional<Executor>(*executor);
  }

  inline int execute(const std::string & name, const std::string & command) const {
    auto executor = getExecutorByName(name);
    
    if (executor) {
      executor->execute(command);
    } else {
      return -1;
    }
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

