#include "executor.hpp"

namespace {
  const std::regex ENTRY_REPLACER("##ENTRY##");
}

int Executor::execute(const std::string & entry) const {
  return system(std::regex_replace(mCommand, ENTRY_REPLACER, entry).c_str());
}

std::vector<std::string> Executor::getSuggestions(const std::string & entry) const {
  return mCompleter->complete(entry);
}
