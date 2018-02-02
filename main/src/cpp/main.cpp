#include <iostream>

#include <mfl/out.hpp>

#include "model/executor.hpp"
#include "model/parser/word_parser.hpp"

int main() {
  Executor executor("name", "command", WordParser(), "[0-9]+");

  std::string parse("Foo Bar fest!!");
  auto parsed = executor.parseSuggestions(parse);

  mfl::out::println("Name: {:s}", executor.getName());
  mfl::out::println("Command: {:s}", executor.getCommand());
  mfl::out::println("Valid: {}", executor.validateEntry(parse));
  mfl::out::println("Parse ({:s}):", parse);
  for (auto & line : parsed) {
    mfl::out::println("- {:s}", line);
  }
  mfl::out::println("Size: {:f} kB",  sizeof(executor) / 1024.0);

  return 0;
}
