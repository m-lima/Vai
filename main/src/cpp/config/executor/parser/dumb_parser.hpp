#pragma once

#include "abstract_parser.hpp"

class DumbParser : public AbstractParser {
public:
  DumbParser() : AbstractParser(
      [&](const std::string & str) {
        return std::vector<std::string> { str };
      }) {}

  std::string getName() const { return "DUMB"; };
};
