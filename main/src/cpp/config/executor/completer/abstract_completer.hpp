#pragma once

#include <string>
#include <vector>
#include <functional>

// TODO: Put the completers in CPP
// TODO: Lazily load completer (most of the time, only one executor is prepared)
// TODO: Alternatively, make completer constexpr (hard if it requires I/O)
class AbstractCompleter : public std::function<std::vector<std::string>(const std::string &)> {
protected:
  AbstractCompleter(const std::function<std::vector<std::string>(const std::string &)> & parser)
      : std::function<std::vector<std::string>(const std::string &)>(parser) {}

public:
  virtual std::string getName() const { return ""; };
};
