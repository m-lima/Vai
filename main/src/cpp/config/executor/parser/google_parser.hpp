#pragma once

#include "abstract_parser.hpp"

#include <sstream>
#include <regex>

class GoogleParser : public AbstractParser {
private:
  static std::vector<std::string> parse(const std::string & str) {
    static const std::regex regex("(\"([^\"]+)\")");

    std::smatch matches;
    std::vector<std::string> list;

    if (!std::regex_search(str, matches, regex)) {
      return list;
    }

    std::string entry = matches.suffix();
    while (std::regex_search(entry, matches, regex)) {
      list.emplace_back(matches[1]);
      entry = matches.suffix();
    }

    return list;
  }
public:
  GoogleParser() : AbstractParser(GoogleParser::parse) {}

  std::string getName() const { return "GOOGLE"; };
};
