#pragma once

#include <string>
#include <vector>
#include <functional>

// TODO: Put the completers in CPP
class AbstractCompleter : public std::function<std::vector<std::string>(const std::string &)> {
protected:
  AbstractCompleter(const std::function<std::vector<std::string>(const std::string &)> & parser)
      : std::function<std::vector<std::string>(const std::string &)>(parser) {}

public:
  virtual std::string getName() const { return ""; };
};
