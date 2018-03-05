#pragma once

#include <string>
#include <sstream>

namespace URLEncoder {
  inline std::string encode(const std::string & str) {
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (std::string::const_iterator i = str.cbegin(), n = str.cend(); i != n; ++i) {
      std::string::value_type c = (*i);

      if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
        escaped << c;
        continue;
      }

      // Any other characters are percent-encoded
      escaped << std::uppercase;
      escaped << '%' << std::setw(2) << int((unsigned char) c);
      escaped << std::nouppercase;
    }

    return escaped.str();
  }
}
