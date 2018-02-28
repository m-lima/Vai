#pragma once

#include "abstract_completer.hpp"

namespace CompleterRegistry {
  AbstractCompleter const getCompleterByName(const std::string & name);
}

