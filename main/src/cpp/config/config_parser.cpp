#include "config_parser.hpp"

const std::regex ConfigParser::Line::REGEX =
    std::regex("^[[:space:]]*((-)?([^:]+))[[:space:]]*(:[[:space:]]*(.+))?[[:space:]]*$]");
