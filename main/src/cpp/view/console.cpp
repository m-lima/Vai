#include "console.hpp"

#include <regex>

#include <mfl/out.hpp>

#include "../executor/executor_store.hpp"
#include "../config/config_manager.hpp"

namespace {

  constexpr auto HELP_COMMAND = "help";

// Helper function to print usage commands
  void printUsage() {
    mfl::out::println("Usage: vai -c EXECUTOR COMMAND\n"
                          " {:<15}{:s}\n" //executor
                          " {:<15}{:s}",  //command
                      "EXECUTOR", "The executor for the command",
                      "COMMAND", "What the executor should perform");
  }

// Helper function to show commands and arguments for the controller
//  void printHelp() {
//    mfl::out::println("Vai::Available commands:\n"
//                        " {:<15}{:<25}{:s}\n" //title
//                        " {:<15}{:<25}{:s}\n" //ctl
//                        " {:<15}{:<25}{:s}\n" //wd
//                        " {:<15}{:<25}{:s}\n" //plugin
//                        " {:<15}{:<25}{:s}\n"
//                        " {:<15}{:<25}{:s}\n"
//                        " {:<15}{:<25}{:s}\n"
//                        " {:<15}{:<25}{:s}\n" //info
//                        " {:<15}{:<25}{:s}",  //quit
//                    "COMMAND", "ARGUMENT", "DESCRIPTION",
//                    "ctl", "start|stop|restart", "Control the child process",
//                    "wd", "on|off", "Control the watchdog",
//                    "plugin", "on|off|list|load|unload|info", "Manage the plugin system",
//                    "", "", "Load requires the path to the plugin to load",
//                    "", "", "Unload requires the index of to the plugin to unload",
//                    "", "", "Info requires the index of to the plugin to query",
//                    "info", "", "Show current wrapper status",
//                    "quit", "", "Stop the wrapper");
//  }

  int listen(const std::string & executor = "", const std::string & command = "") {
  }
}

int Console::start(const std::string & configFolder,
                   const std::string & executorName,
                   const std::string & command) {

  if (executorName == HELP_COMMAND) {
    printUsage();
  }

  ConfigManager configManager(configFolder);
  ExecutorStore executorStore();
}


//int main(int argc, char * argv[]) {
//
//  // HELP ME!!!
//  if (mfl::args::findOption(argv, argv + argc, "-h")) {
//    printUsage();
//    return 0;
//  }
//
//  // Get the command
//  auto command = mfl::args::extractOption(argv, argv + argc, "-c");
//  if (command == 0) {
//    mfl::out::println(stderr, "No command was given");
//    printUsage();
//    return -1;
//  }
//
//  // Get the plugin
//  // If not given, no biggies
//  auto plugin = mfl::args::extractOption(argv, argv + argc, "-p");
//
//  // Command parser
//  const std::regex regex("^:[[:space:]]*"
//                             "(help|ctl|wd|plugin|info|quit)"
//                             "([[:space:]]+(on|off|start|stop|restart|load|list|unload|info))*"
//                             "([[:space:]]+(.+))*"
//                             "[[:space:]]*$");
//
//  // Get the wrapper going
//  Controller controller(command, plugin);
//  controller.start();
//
//  // Main loop
//  std::string buffer;
//  std::smatch match;
//  while (std::getline(std::cin, buffer)) {
//    if (buffer.length() > 1 && buffer[0] == ':') {
//      if (std::regex_match(buffer, match, regex)) {
//        if (match[1] == "help") {
//          // Help
//          printHelp();
//
//        } else if (match[1] == "quit") {
//          // Quit
//          controller.stop();
//          std::exit(0);
//
//        } else if (match[1] == "info") {
//          // Quit
//          controller.printStatus();
//
//        } else if (match[1] == "ctl") {
//          // Control
//          if (match[3] == "start") {
//            controller.start();
//          } else if (match[3] == "stop") {
//            controller.stop();
//          } else if (match[3] == "restart") {
//            controller.stop();
//            controller.start();
//          } else {
//            util::println(stderr, "Invalid argument: {:s}", match[3]);
//          }
//
//        } else if (match[1] == "wd") {
//          // Watchdog
//          if (match[3] == "on") {
//            controller.setWatchdog(true);
//          } else if (match[3] == "off") {
//            controller.setWatchdog(false);
//          } else {
//            util::println(stderr, "WRAPPER::Invalid argument: {:s}", match[3]);
//          }
//
//        } else if (match[1] == "plugin") {
//          // Plugin
//          if (match[3] == "on") {
//            controller.setPluginsActive(true);
//          } else if (match[3] == "off") {
//            controller.setPluginsActive(false);
//          } else if (match[3] == "list") {
//            util::println(controller.getPlugins());
//          } else if (match[3] == "load") {
//            controller.loadPlugin(match[5]);
//          } else if (match[3] == "unload") {
//            controller.unloadPlugin(match[5]);
//          } else if (match[3] == "info") {
//            controller.printPluginInfo(match[5]);
//          } else {
//            util::println(stderr, "WRAPPER::Invalid argument: {:s}", match[3]);
//          }
//        }
//
//      } else {
//        util::println(stderr,
//                      "Command not recognized: {:s}", util::trim(buffer.substr(1)));
//        util::println(stderr,
//                      "Try :help to see supported commands");
//      }
//    } else {
//      // Just relay to the process
//      controller << buffer;
//    }
//  }
//
//  std::exit(0);
//}
