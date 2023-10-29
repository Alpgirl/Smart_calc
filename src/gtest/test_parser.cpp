#include <gtest/gtest.h>

extern "C" {
#include "../back/calc.h"
}

TEST(ParseTest0, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("-2", &size);
  EXPECT_EQ(size, 2);
  EXPECT_EQ(parsed_str[0].code, UMINUS);
  EXPECT_EQ(parsed_str[1].type, NUMBER);
  EXPECT_FLOAT_EQ(parsed_str[1].value, 2.0);
  free(parsed_str);
}

TEST(ParseTest1, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("3mod2", &size);
  EXPECT_EQ(size, 3);
  EXPECT_EQ(parsed_str[0].type, NUMBER);
  EXPECT_FLOAT_EQ(parsed_str[0].value, 3.0);
  EXPECT_EQ(parsed_str[1].code, MOD);
  EXPECT_EQ(parsed_str[2].type, NUMBER);
  EXPECT_FLOAT_EQ(parsed_str[2].value, 2.0);
  EXPECT_EQ(parsed_str[3].type, VOID);
  free(parsed_str);
}

TEST(ParseTest2, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("2 -(x * sin(5))", &size);
  EXPECT_EQ(size, 10);
  EXPECT_EQ(parsed_str[0].type, NUMBER);
  EXPECT_FLOAT_EQ(parsed_str[0].value, 2.0);
  EXPECT_EQ(parsed_str[1].code, MINUS);
  EXPECT_EQ(parsed_str[2].type, BRACKET);
  EXPECT_EQ(parsed_str[2].code, '(');
  EXPECT_EQ(parsed_str[3].type, VAR);
  EXPECT_EQ(parsed_str[4].type, OPERATION);
  EXPECT_EQ(parsed_str[4].code, MULT);
  EXPECT_EQ(parsed_str[5].type, FUNCTION);
  EXPECT_EQ(parsed_str[5].code, SIN);
  free(parsed_str);
}

TEST(ParseTest3, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("2..02", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str(".202", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("202.", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);
  free(parsed_str);
}

TEST(ParseTest4, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("2+", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("+", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("sin", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("3x", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("sin+cos", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("sin+cos", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("2sin(2)", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("()", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("2+-3", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("1+2)2", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str(")2*3", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("*4", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("2*xsin(x)", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str("sos(x)", &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  free(parsed_str);
}

TEST(ParseTest5, ParseCheck) {
  int size = 0;
  token *parsed_str = parse_str("x", &size);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(parsed_str[0].type, VAR);

  free(parsed_str);
}
