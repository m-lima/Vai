#pragma once

#include "abstract_parser.hpp"

class ParserRegistry {
public:
  static AbstractParser getParserByName(const std::string & name);
};

