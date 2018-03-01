#pragma once

#include "abstract_completer.hpp"

#include <sstream>
#include <regex>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

class DuckCompleter : public AbstractCompleter {
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

    static const std::regex regex("(\\{\"phrase\":\"([^\"]+)\"\\})");

    std::smatch matches;
    std::string entry = stringStream.str();
    while (std::regex_search(entry, matches, regex)) {
      list.emplace_back(matches[2]);
      entry = matches.suffix();
    }

    return list;
  }
public:
  DuckCompleter() noexcept : AbstractCompleter(DuckCompleter::parse) {}

  static constexpr auto NAME = "DUCK";
  const std::string getName() const override { return NAME; };
};
