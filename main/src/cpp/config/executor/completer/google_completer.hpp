#pragma once

#include <string>

#include "abstract_completer.hpp"

class GoogleCompleter : public AbstractCompleter {
private:

public:
  GoogleCompleter() noexcept;

  static constexpr auto NAME = "GOOGLE";
  inline const std::string getName() const override { return NAME; };
};
