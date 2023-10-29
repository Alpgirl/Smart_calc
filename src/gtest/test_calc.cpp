#include <gtest/gtest.h>

extern "C" {
#include "../back/calc.h"
}

TEST(CalcTest0, CalcCheck) {
  int size = 0;
  char expr[] = "3-2";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_FLOAT_EQ(res, 1.0);

  free(infix);
  free(postfix);
}

TEST(CalcTest1, CalcCheck) {
  int size = 0;
  char expr[] = "-2^2^2*3 * sqrt(4)";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_FLOAT_EQ(res, -96.0);

  free(infix);
  free(postfix);
}

TEST(CalcTest2, CalcCheck) {
  int size = 0;
  char expr[] = "-(sin(0))";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_FLOAT_EQ(res, 0.0);

  free(infix);
  free(postfix);
}

TEST(CalcTest3, CalcCheck) {
  int size = 0;
  char expr[] = "log(2*5)*2";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_EQ(res, 2);

  free(infix);
  free(postfix);
}

TEST(CalcTest4, CalcCheck) {
  int size = 0;
  char expr[] = "cos(sin(0))";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_EQ(res, 1);

  free(infix);
  free(postfix);
}

TEST(CalcTest5, CalcCheck) {
  int size = 0;
  char expr[] = "sqrt(4^2)";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_EQ(res, 4);

  free(infix);
  free(postfix);
}

TEST(CalcTest6, CalcCheck) {
  int size = 0;
  char expr[] = "ln0";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_NE(res, res);

  free(infix);
  free(postfix);
}

TEST(CalcTest7, CalcCheck) {
  int size = 0;
  char expr[] = "1 / 0";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_NE(res, res);

  free(infix);
  free(postfix);
}

TEST(CalcTest8, CalcCheck) {
  int size = 0;
  char expr[] = "asin(0.9+0.9)";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_NE(res, res);

  free(infix);
  free(postfix);
}

TEST(CalcTest9, CalcCheck) {
  int size = 0;
  char expr[] = "sqrt(-1)";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_NE(res, res);

  free(infix);
  free(postfix);
}

TEST(CalcTest10, CalcCheck) {
  int size = 0;
  char expr[] = "+3 mod 2 mod 1 + 1 + acos1 + atan0 + tan(0)";

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, 0, size);

  EXPECT_EQ(res, 1);

  free(infix);
  free(postfix);
}

TEST(CalcTest11, CalcCheck) {
  int size = 0;
  char expr[] = "0.5*x";

  double var = 2;

  token *infix = parse_str(expr, &size);
  token *postfix = to_polish(infix, size);
  double res = calc(postfix, var, size);

  EXPECT_EQ(res, 1);

  free(infix);
  free(postfix);
}
