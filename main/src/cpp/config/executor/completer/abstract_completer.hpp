#pragma once

#include <string>
#include <vector>

// TODO: Put the completers in CPP
// TODO: Lazily load completer (most of the time, only one executor is prepared)
// TODO: Alternatively, make completer constexpr (hard if it requires I/O)
// TODO: Can make constexpr with static functions in CPP
class AbstractCompleter {
public:
  virtual const std::string getName() const = 0;
  virtual const std::vector<std::string> complete(const std::string &) const = 0;
};
