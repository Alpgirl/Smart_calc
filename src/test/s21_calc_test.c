#include "test.h"

START_TEST(calc_test_0) {
  int size = 0;
  token *infix = parse_str("3-2", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == 1.0, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_1) {
  int size = 0;
  token *infix = parse_str("-2^2^2*3 * sqrt(4)", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == -96.0, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_2) {
  int size = 0;
  token *infix = parse_str("-(sin(0))", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == 0.0, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_3) {
  int size = 0;
  token *infix = parse_str("log(2*5)*2", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == 2, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_4) {
  int size = 0;
  token *infix = parse_str("cossin0", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == 1, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_5) {
  int size = 0;
  token *infix = parse_str("sqrt4^2", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);
  ck_assert_int_eq(res == 4, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_6) {
  int size = 0;
  token *infix = parse_str("ln0", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);

  ck_assert_int_eq(res != res, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_7) {
  int size = 0;
  token *infix = parse_str("1 / 0", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);

  ck_assert_int_eq(res != res, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_8) {
  int size = 0;
  token *infix = parse_str("asin(0.9+0.9)", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);

  ck_assert_int_eq(res != res, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_9) {
  int size = 0;
  token *infix = parse_str("sqrt(-1)", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);

  ck_assert_int_eq(res != res, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_10) {
  int size = 0;
  token *infix =
      parse_str("+3 mod 2 mod 1 + 1 + acos1 + atan0 + tan(0)", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 0, size);

  ck_assert_int_eq(res == 1, 1);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(calc_test_11) {
  int size = 0;
  token *infix = parse_str("0.5*x", &size);
  token *postfix = to_polish(infix, size);

  double res = calc(postfix, 2, size);

  ck_assert_int_eq(res == 1, 1);

  free(infix);
  free(postfix);
}
END_TEST

Suite *calc_test(void) {
  Suite *s1 = suite_create("calc test");

  TCase *calc_tests = tcase_create("test");
  suite_add_tcase(s1, calc_tests);
  tcase_add_test(calc_tests, calc_test_0);
  tcase_add_test(calc_tests, calc_test_1);
  tcase_add_test(calc_tests, calc_test_2);
  tcase_add_test(calc_tests, calc_test_3);
  tcase_add_test(calc_tests, calc_test_4);
  tcase_add_test(calc_tests, calc_test_5);
  tcase_add_test(calc_tests, calc_test_6);
  tcase_add_test(calc_tests, calc_test_7);
  tcase_add_test(calc_tests, calc_test_8);
  tcase_add_test(calc_tests, calc_test_9);
  tcase_add_test(calc_tests, calc_test_10);
  tcase_add_test(calc_tests, calc_test_11);

  return s1;
}