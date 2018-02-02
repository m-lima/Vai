#include <gtest/gtest.h>

#include "../../../../main/src/cpp/model/executor.hpp"
#include "../../../../main/src/cpp/model/parser/word_parser.hpp"

TEST(word_parser_test, parsing) {
  WordParser tested = WordParser();
  auto output = tested("Marcelo wuz here!");
  std::string expected[] = {"Marcelo", "wuz", "here!"};

  EXPECT_EQ(output.size(), 3);
  for (int i = 0; i < 3; ++i) {
    EXPECT_EQ(output[i], expected[0]);
  }
}
