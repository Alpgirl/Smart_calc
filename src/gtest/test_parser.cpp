#include <gtest/gtest.h>

extern "C" {
#include "../back/calc.h"
}

TEST(ParseTest0, ParseCheck) {
  int size = 0;
  char expr[] = "-2";

  token *parsed_str = parse_str(expr, &size);

  EXPECT_EQ(size, 2);
  EXPECT_EQ(parsed_str[0].code, UMINUS);
  EXPECT_EQ(parsed_str[1].type, NUMBER);
  EXPECT_FLOAT_EQ(parsed_str[1].value, 2.0);

  free(parsed_str);
}

TEST(ParseTest1, ParseCheck) {
  int size = 0;
  char expr[] = "3mod2";

  token *parsed_str = parse_str(expr, &size);

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
  char expr[] = "2 -(x * sin(5))";

  token *parsed_str = parse_str(expr, &size);

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
  char expr1[] = "2..02";
  char expr2[] = ".202";
  char expr3[] = "202.";

  token *parsed_str = parse_str(expr1, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str(expr2, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  parsed_str = parse_str(expr3, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);
  free(parsed_str);
}

TEST(ParseTest4, ParseCheck) {
  int size = 0;

  char expr1[] = "2+";
  token *parsed_str = parse_str(expr1, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr2[] = "";
  parsed_str = parse_str(expr2, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr3[] = "+";
  parsed_str = parse_str(expr3, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr4[] = "sin";
  parsed_str = parse_str(expr4, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr5[] = "3x";
  parsed_str = parse_str(expr5, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr6[] = "sin+cos";
  parsed_str = parse_str(expr6, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr7[] = "2sin(2)";
  parsed_str = parse_str(expr7, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr8[] = "()";
  parsed_str = parse_str(expr8, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr10[] = "2+-3";
  parsed_str = parse_str(expr10, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr11[] = "1+2)2";
  parsed_str = parse_str(expr11, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr12[] = ")2*3";
  parsed_str = parse_str(expr12, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr13[] = "*4";
  parsed_str = parse_str(expr13, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr14[] = "2*xsin(x)";
  parsed_str = parse_str(expr14, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  char expr15[] = "sos(x)";
  parsed_str = parse_str(expr15, &size);
  EXPECT_EQ(size, 0);
  EXPECT_EQ(parsed_str, nullptr);

  free(parsed_str);
}

TEST(ParseTest5, ParseCheck) {
  int size = 0;
  char expr[] = "x";

  token *parsed_str = parse_str(expr, &size);
  EXPECT_EQ(size, 1);
  EXPECT_EQ(parsed_str[0].type, VAR);

  free(parsed_str);
}
