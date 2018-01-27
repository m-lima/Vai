#include <iostream>

#include "model/executor.hpp"
#include "model/parser/word_parser.hpp"

int main() {
  std::cout << "Vai!!" << std::endl;

  Executor executor("name", "command", WordParser(), "[0-9]+");

  std::string parse("Foo Bar fest!!");
  auto parsed = executor.parseSuggestions(parse);
  std::cout << "Name: " << executor.getName() << std::endl;
  std::cout << "Command: " << executor.getCommand() << std::endl;
  std::cout << "Valid: " << (executor.validateEntry(parse) ? "True" : "False") << std::endl;
  std::cout << "Parse (" << parse << "):" << std::endl;
  for (auto & line : parsed) {
    std::cout << "  " << line << std::endl;
  }

  return 0;
}
