#pragma once

#include "abstract_completer.hpp"

class DumbCompleter : public AbstractCompleter {
public:
  static constexpr auto NAME = "DUMB";
  inline const std::string getName() const override { return NAME; };
  inline const std::vector<std::string> complete(const std::string & str) const override {
    return {str};
  }
};
