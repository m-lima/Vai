#include "config/executor/completer/duck_completer.hpp"
#include "config/executor/completer/google_completer.hpp"
#include "config/executor/executor_manager.hpp"

#include <mfl/out.hpp>
#include <curlpp/cURLpp.hpp>

void testDuck() {
  DuckCompleter completer;
  for (const auto & item : completer.complete("https://duckduckgo.com/ac/?q=yo")) {
    mfl::out::println("Item: {:s}", item);
  }
}

void testGoogle() {
  GoogleCompleter completer;
  for (const auto & item : completer.complete("http://suggestqueries.google.com/complete/search?output=toolbar&q=yo")) {
    mfl::out::println("Item: {:s}", item);
  }
}

void testParsers() {
  mfl::out::println("## Duck");
  testDuck();

  mfl::out::println();

  mfl::out::println("## Google");
  testGoogle();
}

void testStartsWith(const std::string & str) {
  std::vector<std::string> allValues = {
      "duck",
      "ducker",
      "google",
      "dugo"
  };

  std::vector<std::string> out;

  std::remove_copy_if(allValues.cbegin(), allValues.cend(), std::back_inserter(out),
                      [&str](const auto & value) {
                        return value.compare(0, str.size(), str);
                      });
//  for (const auto & v : allValues) {
//    if (!v.compare(0, str.size(), str)) {
//      out.emplace_back(v);
//    }
//  }

  for (const auto & v : allValues) {
    mfl::out::println(v);
  }

  mfl::out::println();

  for (const auto & v : out) {
    mfl::out::println(v);
  }
}

int main() {
//  curlpp::Cleanup myCleanup;
//  testParsers();

  testStartsWith("du");
  return 0;
}
