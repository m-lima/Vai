#pragma once

#include "abstract_parser.hpp"

namespace ParserRegistry {
  AbstractParser const getParserByName(const std::string & name);
};

