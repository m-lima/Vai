#pragma once

#include <string>

#include "executor.hpp"

class ExecutorParser {
private:
  Executor * executor;

  ExecutorParser(Executor * target) : executor(target) {}

  bool parse(const std::string & key, const std::string & value);

  bool isValid() const {
    return executor
           && !executor->getName().empty()
           && !executor->getCommand().empty();
  }

public:

  template<typename StreamReader>
  static constexpr bool parse(StreamReader & reader,
                              Executor & executor,
                              int indentation) {
    ExecutorParser parser(&executor);

    do {
      if (reader.line.indentation < indentation) {
        break;
      }

      if (!parser.parse(reader.line.key, reader.line.value)) {
        reader.error = "Failure parsing executor";
        return false;
      }
    } while (reader.readNext(indentation));

    if (parser.isValid()) {
      return true;
    }

    if (reader.error.empty()) {
      reader.error = "Invalid executor object";
    }
    return false;
  }

  template<typename Stream>
  static constexpr bool save(Stream & stream,
                             const Executor & executor,
                             int indentation) {
    if (executor.getName().empty() || executor.getCommand().empty()) {
      return true;
    }

    fmt::print(stream, "name: {:s}\n", executor.getName());
    fmt::print(stream,
               fmt::format("{{:<{:d}}}command: {:s}\n",
                           indentation,
                           executor.getCommand()),
               "");
    if (!executor.getValidator().empty() && executor.getValidator() != ".*") {
      fmt::print(stream,
                 fmt::format("{{:<{:d}}}validator: {:s}\n",
                             indentation,
                             executor.getValidator()),
                 "");
    }

    if (!executor.getParser().empty() && executor.getParser() != "DUMB") {
      fmt::print(stream,
                 fmt::format("{{:<{:d}}}parser: {:s}\n",
                             indentation,
                             executor.getParser()),
                 "");
    }

    return true;
  }
};
