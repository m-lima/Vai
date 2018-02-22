#include "parser_registry.hpp"

#include <array>

#include "word_parser.hpp"
#include "dumb_parser.hpp"

namespace {
  static constexpr int KNOWN_PARSERS_COUNT = 2;
  const static std::array<AbstractParser, KNOWN_PARSERS_COUNT> _knwonParsers = {
      DumbParser(),
      WordParser()
  };
  const static std::array<std::string, KNOWN_PARSERS_COUNT> _knwonParserNames = {
      _knwonParsers[0].getName(),
      _knwonParsers[1].getName()
  };
}

AbstractParser ParserRegistry::getParserByName(const std::string & name) {
  if (name.empty()) {
    return _knwonParsers[0];
  }

  for (int i = 0; i < KNOWN_PARSERS_COUNT; ++i) {
    if (_knwonParserNames[i] == name) {
      return _knwonParsers[i];
    }
  }

  return _knwonParsers[0];
}
