#include "duck_completer.hpp"

#include <regex>
#include <sstream>

#include <mfl/out.hpp>
#include <curlpp/Options.hpp>

namespace {
  const std::regex REGEX("(\\{\"phrase\":\"([^\"]+)\"\\})");
}

const std::vector<std::string> DuckCompleter::complete(const std::string & str) const {
  std::vector<std::string> list;
  std::ostringstream stringStream;

  try {
    stringStream << curlpp::options::Url(str);
  } catch (curlpp::RuntimeError & e) {
    mfl::out::println(stderr, "Failed getting duck completion: {}", e.what());
    return list;
  } catch (curlpp::LogicError & e) {
    mfl::out::println(stderr, "Failed getting duck completion: {}", e.what());
    return list;
  }

  std::smatch matches;
  std::string entry = stringStream.str();
  while (std::regex_search(entry, matches, REGEX)) {
    list.emplace_back(matches[2]);
    entry = matches.suffix();
  }

  return list;
}
