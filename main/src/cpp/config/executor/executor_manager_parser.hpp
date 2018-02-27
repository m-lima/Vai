#pragma once

#include "executor_manager.hpp"
#include "executor_parser.hpp"

namespace ExecutorManagerParser {

  template<typename StreamReader>
  constexpr bool parse(StreamReader & reader,
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

  template<typename Stream>
  constexpr bool save(Stream & stream,
                      const ExecutorManager & executorManager,
                      int indentation) {
    for (const auto & executor : executorManager.executors) {
      fmt::print(stream, fmt::format("{{:<{:d}}}-", indentation), "");
      if (!ExecutorParser::save(stream, executor, indentation + 1)) {
        return false;
      }
    }

    return true;
  }
};

