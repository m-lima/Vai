#pragma once

#include "abstract_parser.hpp"

#include <sstream>
#include <regex>

class DuckParser : public AbstractParser {
private:
  static std::vector<std::string> parse(const std::string & str) {
    static const std::regex regex("(\\{\"phrase\":\"([^\"]+)\"\\})");

    std::smatch matches;
    std::string entry = str;
    std::vector<std::string> list;
    while (std::regex_search(entry, matches, regex)) {
      list.emplace_back(matches[2]);
      entry = matches.suffix();
    }

    return list;
  }
public:
  DuckParser() : AbstractParser(DuckParser::parse) {}

  std::string getName() const { return "DUCK"; };
};
