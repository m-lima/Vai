#include "config_parser.hpp"

namespace ConfigParser {
  const std::regex Line::REGEX = std::regex("^[[:space:]]*"
                                                "((-)?([^:]+))"
                                                "[[:space:]]*"
                                                "(:[[:space:]]*(.+))?"
                                                "[[:space:]]*$");
}
