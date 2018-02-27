#pragma once

#include "executor_manager.hpp"
#include "executor_parser.hpp"

namespace ExecutorManagerParser {

  template <typename StreamReader>
  bool parse(StreamReader & reader,
             ExecutorManager & executorManager,
             int indentation) {
    executorManager.executors.clear();

    if (!reader.readNext(indentation)) {
      return false;
    }

    while (reader.line.indentation == indentation) {
      Executor executor;
      if (reader.line.popListItem()) {
        if (ExecutorParser::parse(reader, executor, indentation + 1)) {
          executorManager.executors.push_back(executor);
        } else {
          return false;
        }
      } else {
        reader.error = "Was expecting a list item";
        return false;
      }
    }

    return true;
  }
};

