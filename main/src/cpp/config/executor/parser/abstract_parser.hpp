#pragma once

#include <string>
#include <vector>
#include <functional>

class AbstractParser : public std::function<std::vector<std::string>(const std::string &)> {
protected:
  AbstractParser(const std::function<std::vector<std::string>(const std::string &)> & parser)
      : std::function<std::vector<std::string>(const std::string &)>(parser) {}

public:
  virtual std::string getName() const {
    return "DUMB";
  };
};
