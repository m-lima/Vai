#include "completer_registry.hpp"

#include "dumb_completer.hpp"
#include "duck_completer.hpp"
#include "google_completer.hpp"

namespace {
  const DumbCompleter dumbCompleter = DumbCompleter();
  const DuckCompleter duckCompleter = DuckCompleter();
  const GoogleCompleter googleCompleter = GoogleCompleter();
}

const AbstractCompleter * CompleterRegistry::getCompleterByName(const std::string & name) {
  if (name.empty() || name == DumbCompleter::NAME) {
    return &dumbCompleter;
  }

  if (name == DuckCompleter::NAME) {
    return &duckCompleter;
  }

  if (name == GoogleCompleter::NAME) {
    return &googleCompleter;
  }

  return &dumbCompleter;
}
