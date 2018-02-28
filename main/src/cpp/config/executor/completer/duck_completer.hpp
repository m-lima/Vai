#pragma once

#include "abstract_completer.hpp"

#include <sstream>
#include <regex>

class DuckCompleter : public AbstractCompleter {
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
  DuckCompleter() : AbstractCompleter(DuckCompleter::parse) {}

  static constexpr auto NAME = "DUCK";
  const std::string getName() const override { return NAME; };
};
