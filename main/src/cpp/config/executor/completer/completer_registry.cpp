#include "completer_registry.hpp"

#include "dumb_completer.hpp"
#include "duck_completer.hpp"
#include "google_completer.hpp"

// TODO: Make constexpr
namespace {
  constexpr int KNOWN_COMPLETER_COUNT = 3;
  const AbstractCompleter * _knwonCompleters[KNOWN_COMPLETER_COUNT] = {
      new DumbCompleter(),
      new DuckCompleter(),
      new GoogleCompleter()
  };
  constexpr const char * _knwonCompleterNames[KNOWN_COMPLETER_COUNT] = {
      DumbCompleter::NAME,
      DuckCompleter::NAME,
      GoogleCompleter::NAME
  };
}

const AbstractCompleter * CompleterRegistry::getCompleterByName(const std::string & name) {
  if (name.empty()) {
    return _knwonCompleters[0];
  }

  for (int i = 0; i < KNOWN_COMPLETER_COUNT; ++i) {
    if (_knwonCompleterNames[i] == name) {
      return _knwonCompleters[i];
    }
  }

  return _knwonCompleters[0];
}
