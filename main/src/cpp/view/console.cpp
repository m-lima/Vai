#include "console.hpp"

#include <mfl/out.hpp>

#include "../config/config_manager.hpp"

namespace {

  constexpr char HELP_COMMAND[] = "help";

// Helper function to print usage commands
  void printUsage() {
    mfl::out::println("Usage: vai EXECUTOR COMMAND\n"
                          " {:<15}{:s}\n" //executor
                          " {:<15}{:s}",  //command
                      "EXECUTOR", "The executor for the command",
                      "COMMAND", "What the executor should perform");
  }

}

int Console::start(const std::string & executorName,
                   const std::string & command) {

  if (executorName == HELP_COMMAND) {
    printUsage();
    return 0;
  }

  ConfigManager configManager;

  if (command.empty()) {
    for (const auto & executor
        : configManager.executorManager.getPossibleExecutors(executorName)) {
      mfl::out::println(executor);
    }
    return 0;
  }

  return configManager.executorManager.execute(executorName, command);
}
