#include "executor.hpp"

std::string Executor::getExecutorCommand(const std::string & entry) const {
  static const std::regex ENTRY_REPLACER("##ENTRY##");
  return std::regex_replace(mCommand, ENTRY_REPLACER, entry);
}
