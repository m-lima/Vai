#pragma once

#include "abstract_completer.hpp"

#include <sstream>
#include <regex>

class GoogleCompleter : public AbstractCompleter {
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
  GoogleCompleter() : AbstractCompleter(GoogleCompleter::parse) {}

  static constexpr auto NAME = "GOOGLE";
  const std::string getName() const override { return NAME; };
};
