#pragma once

#include <string>

#include "abstract_completer.hpp"

class DuckCompleter : public AbstractCompleter {
public:
  static constexpr auto NAME = "DUCK";
  inline const std::string getName() const override { return NAME; };
  const std::vector<std::string> complete(const std::string &) const override;
};
