#pragma once

#include <string>

#include "abstract_completer.hpp"

class GoogleCompleter : public AbstractCompleter {
public:
  static constexpr auto NAME = "GOOGLE";
  inline const std::string getName() const override { return NAME; };
  const std::vector<std::string> complete(const std::string &) const override;
};
