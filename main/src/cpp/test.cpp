#include "config/executor/executor.hpp"
#include "config/executor/completer/duck_completer.hpp"
#include "config/executor/completer/google_completer.hpp"

#include <mfl/out.hpp>

void testDuck() {
  DuckCompleter completer;
  std::string result = "[{\"phrase\":\"youtube\"},{\"phrase\":\"youtube converter\"},{\"phrase\":\"youtube music\"},{\"phrase\":\"youtube mp3\"},{\"phrase\":\"youtube video\"},{\"phrase\":\"youtube downloader\"},{\"phrase\":\"youtube movies\"},{\"phrase\":\"young and the restless\"},{\"phrase\":\"yoga\"},{\"phrase\":\"you\"}]";

  for (const auto item : completer(result)) {
    mfl::out::println("Item: {:s}", item);
  }
}

void testGoogle() {
  GoogleCompleter completer;
  std::string result = "[\"yo\",[\"youtube\",\"you\",\"youtube to mp3\",\"yoga\",\"yo\",\"youtube converter\",\"youtube downloader\",\"youwish\",\"youngstorget\",\"yoy\"]]";

  for (const auto item : completer(result)) {
    mfl::out::println("Item: {:s}", item);
  }
}

int main(int argc, char * argv[]) {
  Executor executor;
  executor.setName("yo");
  mfl::out::println(executor.getName());

  mfl::out::println("## Duck");
  testDuck();

  mfl::out::println();

  mfl::out::println("## Google");
  testGoogle();

  return 0;
}

