#pragma once

#include "abstract_Completer.hpp"

namespace CompleterRegistry {
  AbstractCompleter const getCompleterByName(const std::string & name);
};

