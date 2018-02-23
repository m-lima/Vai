#include <string>

#include <rapidjson/reader.h>

#include "config/config_parser.hpp"

constexpr auto json = R"json"(
{
  "executors": [
    {
      "command": "Dumb command",
      "name": "Dumb",
      "parser": "DUMB",
      "validator": ".*"
    },
    {
      "command": "Word command",
      "name": "Word",
      "parser": "DUMB",
      "validator": ".*"
    }
  ]
}
)json"";

int main(int argc, char * argv[]) {
  ConfigParser parser;
  rapidjson::Reader reader;
  rapidjson::StringStream stream(json);
  
  reader.Parse(stream, parser);
}

