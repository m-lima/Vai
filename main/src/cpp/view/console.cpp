#include "console.hpp"

#include <string>
#include <sstream>
#include <vector>
#include <optional>

#include <ncurses.h>
#include <mfl/out.hpp>

#include "../config/config_manager.hpp"
#include "../config/executor/executor.hpp"

namespace {
  std::string _executorName;
  std::string _command;
  std::vector<std::string> _emptyCompletions;

  constexpr short GREEN = 1;
  constexpr short WHITE = 2;
  constexpr short BLUE = 3;

  enum InputAction {
    CONTINUE,
    ABORT,
    EXECUTE
  };

  void initializeColors() {
    start_color();

    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  }

  void printScreen(const std::vector<std::string> & completions) {

    clear();
//    attron(COLOR_PAIR(GREEN));
    printw("\033[32m");
    printw(_executorName.c_str());
    printw(" ");

//    attron(COLOR_PAIR(WHITE));
    printw("\033[0m");
    printw(_command.c_str());
    printw("\n");

//    attron(COLOR_PAIR(BLUE));
    printw("\033[34m");
    for (auto & completion : completions) {
      printw(completion.c_str());
      printw("\n");
    }

    attron(COLOR_PAIR(WHITE));
    move(0, _executorName.length() + 1 + _command.length());

    refresh();
  }

  InputAction getAction(int c) {
    switch (c) {
      case 0: // Null
      case 4: // CTRL+D
      case 27: // Escape
        return ABORT;
      case 2: // CTRL+B
        return CONTINUE;
      case 6: // CTRL+F
        return CONTINUE;
      case 10: // Return
        return EXECUTE;
    }

    return CONTINUE;
  }
}

Console::Console(int argc, char * argv[]) {
  if (argc > 2) {
    _command = Executor::concatenateCommand<0>(argc, argv);
  }

  if (argc > 1) {
    _executorName = std::string(argv[1]);
  }
}

int Console::start() {
  initscr();
//  noecho();
//  initializeColors();

  InputAction inputAction = CONTINUE;
  std::optional<Executor> executor;

  while(inputAction != EXECUTE && inputAction != ABORT) {
    executor = mConfigManager.executorManager.getExecutorByName(_executorName);

    printScreen(executor ? executor->complete(_command) : _emptyCompletions);
    int c = getch();
    printw(std::to_string(c).c_str());
    refresh();
    getch();

    inputAction = getAction(c);
  }

  endwin();

  if (inputAction == EXECUTE && executor) {
    return executor->execute(_command);
  }

  return -1;
}


