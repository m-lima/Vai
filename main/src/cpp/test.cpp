#include <string>

#include <rapidjson/reader.h>
#include <mfl/out.hpp>

#include "config/config_parser.hpp"

class bla {
private:
  int ble;
public:
  void setBle(int nova) {ble = nova;}
  int getBle() const {return ble;}
};

class bli {
private:
  bla * blo;
public:
  bli(bla & blu) : blo(&blu) {}
  void doit() { blo->setBle(blo->getBle() * 2); }
};

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
  bla f;
  f.setBle(3);
  mfl::out::println("ble: {:d}", f.getBle());
  bli fo(f);
  mfl::out::println("ble: {:d}", f.getBle());
  fo.doit();
  mfl::out::println("ble: {:d}", f.getBle());

  ConfigParser parser;
  rapidjson::Reader reader;
  rapidjson::StringStream stream(json);
  
  reader.Parse(stream, parser);
}

