#include "executor_store.hpp"
#include "../parser/word_parser.hpp"

#include <unordered_map>

namespace {
  std::unordered_map<std::string, Executor> _executors;
}

ExecutorStore::ExecutorStore(const ConfigManager & configManager) : cConfigManager(configManager) {
}

std::vector<std::string> ExecutorStore::getPossibleExecutors(const std::string & executor) {
  for (auto it = _executors.begin(); it != _executors.end(); ++it) {
    it->first;
  }
  return std::vector<std::string>();
}

const Executor & ExecutorStore::getExecutor(const std::string & executor) const {
  return Executor("name", "command", WordParser(), "[0-9]+");
}
