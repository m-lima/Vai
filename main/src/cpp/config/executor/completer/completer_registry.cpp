#include "completer_registry.hpp"

#include "dumb_completer.hpp"
#include "duck_completer.hpp"
#include "google_completer.hpp"

namespace {
  static const DumbCompleter * const dumbCompleter = new DumbCompleter();
  static const DuckCompleter * duckCompleter = nullptr;
  static const GoogleCompleter * googleCompleter = nullptr;
}

const AbstractCompleter * CompleterRegistry::getCompleterByName(const std::string & name) {
  if (name.empty() || name == DumbCompleter::NAME) {
    return dumbCompleter;
  }

  if (name == DuckCompleter::NAME) {
    if (duckCompleter == nullptr) {
      duckCompleter = new DuckCompleter();
    }
    return duckCompleter;
  }

  if (name == GoogleCompleter::NAME) {
    if (googleCompleter == nullptr) {
      googleCompleter = new GoogleCompleter();
    }
    return googleCompleter;
  }

  return dumbCompleter;
}
