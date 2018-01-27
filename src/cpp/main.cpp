#include <iostream>

#include "model/executor.hpp"

int main(int argc, char** argv) {
  std::cout << "Vai!!" << std::endl;

  Executor executor("name", "command");

  std::cout << "Name: " << executor.getName() << std::endl;
  std::cout << "Command: " << executor.getCommand() << std::endl;

  return 0;
}
