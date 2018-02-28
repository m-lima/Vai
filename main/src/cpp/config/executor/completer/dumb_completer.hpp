#pragma once

#include "abstract_completer.hpp"

class DumbCompleter : public AbstractCompleter {
public:
  DumbCompleter() : AbstractCompleter(
      [&](const std::string & str) {
        return std::vector<std::string> {str};
      }) {}

  std::string getName() const { return "DUMB"; };
};
