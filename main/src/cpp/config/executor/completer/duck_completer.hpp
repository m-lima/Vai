#pragma once

#include <string>

#include "abstract_completer.hpp"

class DuckCompleter : public AbstractCompleter {
private:

public:
  DuckCompleter() noexcept;

  static constexpr auto NAME = "DUCK";
  inline const std::string getName() const override { return NAME; };
};
