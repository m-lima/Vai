#include <string>

#include "view/console.hpp"

std::string concatenateArguments(int argc, char ** argv) {
  if (argc < 2) {
    return "";
  }
  
  if (argc == 3) {
    return argv[2];
  }
  
  std::string command = argv[2];

  for (int i = 3; i < argc; ++i) {
    command = command + " " + argv[i];
  }
  
  return command;
}

int main(int argc, char * argv[]) {
  auto command = concatenateArguments(argc, argv);

  Console console;
  return console.start(argc > 1 ? argv[1] : "", command);
}

