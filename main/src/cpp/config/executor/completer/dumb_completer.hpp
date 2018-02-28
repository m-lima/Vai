#pragma once

#include "abstract_completer.hpp"

class DumbCompleter : public AbstractCompleter {
public:
  DumbCompleter() noexcept : AbstractCompleter(
      [&](const std::string & str) {
        return std::vector<std::string> {str};
      }) {}

  static constexpr auto NAME = "DUMB";
  const std::string getName() const override { return NAME; };
};
