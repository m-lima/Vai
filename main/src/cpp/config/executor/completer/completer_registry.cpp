#include "completer_registry.hpp"

#include "dumb_completer.hpp"
#include "duck_completer.hpp"
#include "google_completer.hpp"

// TODO: Make constexpr
namespace {
  static constexpr int KNOWN_COMPLETER_COUNT = 3;
  static const AbstractCompleter _knwonCompleters[KNOWN_COMPLETER_COUNT] = {
      DumbCompleter(),
      DuckCompleter(),
      GoogleCompleter()
  };
  static const std::string _knwonCompleterNames[KNOWN_COMPLETER_COUNT] = {
      _knwonCompleters[0].getName(),
      _knwonCompleters[1].getName(),
      _knwonCompleters[2].getName()
  };
}

AbstractCompleter const CompleterRegistry::getCompleterByName(const std::string & name){
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
