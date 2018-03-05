#include "config/executor/completer/duck_completer.hpp"
#include "config/executor/completer/google_completer.hpp"

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

int main() {
  curlpp::Cleanup myCleanup;
  testParsers();
  return 0;
}
