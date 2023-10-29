#include <gtest/gtest.h>

extern "C" {
#include "../back/calc.h"
}

TEST(ToPolishTest0, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("3-2", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[1].value, 2.0);

  EXPECT_EQ(postfix[2].type, OPERATION);
  EXPECT_EQ(postfix[2].code, MINUS);

  EXPECT_EQ(postfix[3].type, VOID);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest1, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("3*2^1", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[1].value, 2.0);

  EXPECT_EQ(postfix[2].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[2].value, 1.0);

  EXPECT_EQ(postfix[3].type, OPERATION);
  EXPECT_EQ(postfix[3].code, POW);

  EXPECT_EQ(postfix[4].type, OPERATION);
  EXPECT_EQ(postfix[4].code, MULT);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest2, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("3/2/1", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[1].value, 2.0);

  EXPECT_EQ(postfix[2].type, OPERATION);
  EXPECT_EQ(postfix[2].code, DIV);

  EXPECT_EQ(postfix[3].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[3].value, 1.0);

  EXPECT_EQ(postfix[4].type, OPERATION);
  EXPECT_EQ(postfix[4].code, DIV);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest3, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("sin(3^2)", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[1].value, 2.0);

  EXPECT_EQ(postfix[2].type, OPERATION);
  EXPECT_EQ(postfix[2].code, POW);

  EXPECT_EQ(postfix[3].type, FUNCTION);
  EXPECT_EQ(postfix[3].code, SIN);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest4, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("sin(sin(3))", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, FUNCTION);
  EXPECT_EQ(postfix[1].code, SIN);

  EXPECT_EQ(postfix[2].type, FUNCTION);
  EXPECT_EQ(postfix[2].code, SIN);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest5, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("(3*2)^1", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 3.0);

  EXPECT_EQ(postfix[1].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[1].value, 2.0);

  EXPECT_EQ(postfix[2].type, OPERATION);
  EXPECT_EQ(postfix[2].code, MULT);

  EXPECT_EQ(postfix[3].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[3].value, 1.0);

  EXPECT_EQ(postfix[4].type, OPERATION);
  EXPECT_EQ(postfix[4].code, POW);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest6, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("3-2)", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix == nullptr, 1);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest7, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("(3-2*4^sin(6)", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix == nullptr, 1);

  free(infix);
  free(postfix);
}

TEST(ToPolishTest8, ToPolishCheck) {
  int size = 0;
  token *infix = parse_str("log10 * 3", &size);
  token *postfix = to_polish(infix, size);

  EXPECT_EQ(postfix[0].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[0].value, 10.0);

  EXPECT_EQ(postfix[1].type, FUNCTION);
  EXPECT_EQ(postfix[1].code, LOG);

  EXPECT_EQ(postfix[2].type, NUMBER);
  EXPECT_FLOAT_EQ(postfix[2].value, 3.0);

  EXPECT_EQ(postfix[3].type, OPERATION);
  EXPECT_EQ(postfix[3].code, MULT);

  free(infix);
  free(postfix);
}