#include <iostream>

#include <mfl/out.hpp>
#include <nlohmann/json.hpp>

#include "config/executor/executor.hpp"
#include "config/executor/parser/word_parser.hpp"

#include "view/console.hpp"
#include "config/config_model.hpp"

//void testParser() {
//  Executor executor("name", "command", WordParser(), "[0-9]+");
//
//  std::string parse("Foo Bar fest!!");
//  auto parsed = executor.parseSuggestions(parse);
//
//  mfl::out::println("Name: {:s}", executor.getName());
//  mfl::out::println("Command: {:s}", executor.getCommand());
//  mfl::out::println("Valid: {}", executor.validateEntry(parse));
//  mfl::out::println("Parse ({:s}):", parse);
//  for (auto & line : parsed) {
//    mfl::out::println("- {:s}", line);
//  }
//  mfl::out::println("Size: {:f} kB",  sizeof(executor) / 1024.0);
//}

//void testJson() {
//  std::stringstream stream;
//  stream << "{\n";
//  stream << "  \"executors\": {\n";
//  stream << "    \"bla\": 1,\n";
//  stream << "    \"ble\": 2,\n";
//  stream << "    \"bli\": 3\n";
//  stream << "  }\n";
//  stream << "}\n";
//
//  nlohmann::json json;
//  stream >> json;
//
//  for (auto a : json) {
//    std::cout << a << std::endl;
//  }
//  for (nlohmann::json::iterator it = json.begin(); it != json.end(); ++it) {
//    std::cout << it.key() << '\n';
//  }
//}

constexpr auto yo = R"bla"(
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
)bla"";

nlohmann::json createJson() {
  std::vector<Executor> executors = {{"Dumb", "Dumb command", DumbParser()}, {"Word", "Word command", WordParser()}};
  nlohmann::json json;
  json[ConfigFormat::Executors::Field] = executors;

//  for (auto & executor : executors) {
//    mfl::out::println("Name: {:s}", executor.getName());
//    mfl::out::println("Command: {:s}", executor.getCommand());
//    mfl::out::println("Parser: {:s}", executor.getParser());
//    mfl::out::println("Validator ({:s}):", executor.getValidator());
//  }

  return json;
//  return "";
}

int main() {
//  testParser();
//  testJson();
  auto json = createJson();
  mfl::out::println("{:s}", json.dump(2));
  json = yo;
  json = R"(
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
)"_json;
  mfl::out::println("{:s}", json.dump(4));

//  Console console;
//  std::unordered_map<std::string, std::string> map{};
//  return console.start(map);
}

