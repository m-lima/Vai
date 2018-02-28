#pragma once

#include "abstract_completer.hpp"

namespace CompleterRegistry {
  const AbstractCompleter * getCompleterByName(const std::string & name);
}

