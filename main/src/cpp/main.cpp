#include <string>

#include <mfl/out.hpp>
#include <curlpp/cURLpp.hpp>

#include "view/console.hpp"
#include "config/config_manager.hpp"

void printUsage(std::FILE * output) {
  mfl::out::println(output, "Usage for vai:");
  mfl::out::println(output, "vai [-h|c|e|g] COMMAND [ARGS]");
  mfl::out::println(output, "  {:<15}{}", "h", "Print usage help");
  mfl::out::println(output, "  {:<15}{}", "e", "Get registered executors");
  mfl::out::println(output, "  {:<15}{}", "c", "Output suggestions");
  mfl::out::println(output, "  {:<15}{}", "g", "Load graphical user interface");
  mfl::out::println(output, "  {:<15}{}", "COMMAND", "Which command to use");
  mfl::out::println(output, "  {:<15}{}", "ARGS", "Arguments to be passed to EXECUTOR");
}

template <int Offset>
std::string concatenateArguments(int argc, char ** argv) {
  if (argc < Offset + 3) {
    return "";
  }

  if (argc == Offset + 3) {
    return argv[Offset + 2];
  }

  std::string command = argv[Offset + 2];

  for (int i = Offset + 3; i < argc; ++i) {
    command = command + " " + argv[i];
  }

  return command;
}

int returnError() {
  printUsage(stderr);
  return -1;
}

int showExecutors(int argc, char * argv[]) {
  if (argc > 3) {
    return returnError();
  }

  ConfigManager config;
  for (const auto & executor : config.executorManager.getPossibleExecutors(argc == 2 ? "" : argv[2])) {
    mfl::out::println(executor);
  }

  return 0;
}

int runCommand(int argc, char * argv[]) {
  if (argc < 4) {
    return returnError();
  }

  auto command = concatenateArguments<1>(argc, argv);

  curlpp::Cleanup curlCleanUp;
  ConfigManager config;
  for (const auto & completion : config.executorManager.complete(argv[2], command)) {
    mfl::out::println(completion);
  }

  return 0;
}

int main(int argc, char * argv[]) {
  if (argc < 2) {
    return returnError();
  }

  if (argv[1][0] == '-') {
    if (argv[1][1] == 0 || argv[1][2] != 0) {
      return returnError();
    }

    switch (argv[1][1]) {
      case 'h':
        printUsage(stdout);
        return 0;

      case 'e':
        return showExecutors(argc, argv);

      case 'c':
        return runCommand(argc, argv);

      case 'g':
      default:
        return returnError();
    }
  }

  auto command = concatenateArguments<0>(argc, argv);

  Console console;
  return console.start(argc > 1 ? argv[1] : "", command);
}

