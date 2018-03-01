#pragma once

#include "abstract_completer.hpp"

#include <sstream>
#include <regex>

class GoogleCompleter : public AbstractCompleter {
private:
  static std::vector<std::string> parse(const std::string & str) {

    std::vector<std::string> list;
    std::ostringstream stringStream;

    try {
      stringStream << curlpp::options::Url(str);
    } catch( curlpp::RuntimeError &e ) {
      std::cerr << e.what() << std::endl;
      return list;

    } catch( curlpp::LogicError &e ) {
      std::cerr << e.what() << std::endl;
      return list;
    }

    static const std::regex regex("(\"([^\"]+)\")");

    std::smatch matches;
    std::string entry = stringStream.str();

    if (!std::regex_search(entry, matches, regex)) {
      return list;
    }

    entry = matches.suffix();
    while (std::regex_search(entry, matches, regex)) {
      list.emplace_back(matches[1]);
      entry = matches.suffix();
    }

    return list;
  }
public:
  GoogleCompleter() noexcept : AbstractCompleter(GoogleCompleter::parse) {}

  static constexpr auto NAME = "GOOGLE";
  const std::string getName() const override { return NAME; };
};
