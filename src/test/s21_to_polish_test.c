#include "test.h"

START_TEST(to_polish_test_0) {
  int size = 0;
  token *infix = parse_str("3-2", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, NUMBER);
  ck_assert_int_eq(postfix[1].value == 2.0, 1);

  ck_assert_int_eq(postfix[2].type, OPERATION);
  ck_assert_int_eq(postfix[2].code, MINUS);

  ck_assert_int_eq(postfix[3].type, VOID);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_1) {
  int size = 0;
  token *infix = parse_str("3*2^1", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, NUMBER);
  ck_assert_int_eq(postfix[1].value == 2.0, 1);

  ck_assert_int_eq(postfix[2].type, NUMBER);
  ck_assert_int_eq(postfix[2].value == 1.0, 1);

  ck_assert_int_eq(postfix[3].type, OPERATION);
  ck_assert_int_eq(postfix[3].code, POW);

  ck_assert_int_eq(postfix[4].type, OPERATION);
  ck_assert_int_eq(postfix[4].code, MULT);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_2) {
  int size = 0;
  token *infix = parse_str("3/2/1", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, NUMBER);
  ck_assert_int_eq(postfix[1].value == 2.0, 1);

  ck_assert_int_eq(postfix[2].type, OPERATION);
  ck_assert_int_eq(postfix[2].code, DIV);

  ck_assert_int_eq(postfix[3].type, NUMBER);
  ck_assert_int_eq(postfix[3].value == 1.0, 1);

  ck_assert_int_eq(postfix[4].type, OPERATION);
  ck_assert_int_eq(postfix[4].code, DIV);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_3) {
  int size = 0;
  token *infix = parse_str("sin(3^2)", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, NUMBER);
  ck_assert_int_eq(postfix[1].value == 2.0, 1);

  ck_assert_int_eq(postfix[2].type, OPERATION);
  ck_assert_int_eq(postfix[2].code, POW);

  ck_assert_int_eq(postfix[3].type, FUNCTION);
  ck_assert_int_eq(postfix[3].code, SIN);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_4) {
  int size = 0;
  token *infix = parse_str("sin(sin(3))", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, FUNCTION);
  ck_assert_int_eq(postfix[1].code, SIN);

  ck_assert_int_eq(postfix[2].type, FUNCTION);
  ck_assert_int_eq(postfix[2].code, SIN);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_5) {
  int size = 0;
  token *infix = parse_str("(3*2)^1", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 3.0, 1);

  ck_assert_int_eq(postfix[1].type, NUMBER);
  ck_assert_int_eq(postfix[1].value == 2.0, 1);

  ck_assert_int_eq(postfix[2].type, OPERATION);
  ck_assert_int_eq(postfix[2].code, MULT);

  ck_assert_int_eq(postfix[3].type, NUMBER);
  ck_assert_int_eq(postfix[3].value == 1.0, 1);

  ck_assert_int_eq(postfix[4].type, OPERATION);
  ck_assert_int_eq(postfix[4].code, POW);

  free(infix);
  free(postfix);
}
END_TEST

START_TEST(to_polish_test_6) {
  int size = 0;
  token *infix = parse_str("3-2)", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix == NULL, 1);

  free(infix);
}
END_TEST

START_TEST(to_polish_test_7) {
  int size = 0;
  token *infix = parse_str("(3-2*4^sin(6)", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix == NULL, 1);

  free(infix);
}
END_TEST

START_TEST(to_polish_test_8) {
  int size = 0;
  token *infix = parse_str("log10 * 3", &size);
  token *postfix = to_polish(infix, size);

  ck_assert_int_eq(postfix[0].type, NUMBER);
  ck_assert_int_eq(postfix[0].value == 10.0, 1);

  ck_assert_int_eq(postfix[1].type, FUNCTION);
  ck_assert_int_eq(postfix[1].code, LOG);

  ck_assert_int_eq(postfix[2].type, NUMBER);
  ck_assert_int_eq(postfix[2].value == 3.0, 1);

  ck_assert_int_eq(postfix[3].type, OPERATION);
  ck_assert_int_eq(postfix[3].code, MULT);

  free(infix);
  free(postfix);
}
END_TEST

Suite *to_polish_test(void) {
  Suite *s1 = suite_create("to_polish tests");

  TCase *to_polish_tests = tcase_create("to polish tests");
  suite_add_tcase(s1, to_polish_tests);
  tcase_add_test(to_polish_tests, to_polish_test_0);
  tcase_add_test(to_polish_tests, to_polish_test_1);
  tcase_add_test(to_polish_tests, to_polish_test_2);
  tcase_add_test(to_polish_tests, to_polish_test_3);
  tcase_add_test(to_polish_tests, to_polish_test_4);
  tcase_add_test(to_polish_tests, to_polish_test_5);
  tcase_add_test(to_polish_tests, to_polish_test_6);
  tcase_add_test(to_polish_tests, to_polish_test_7);
  tcase_add_test(to_polish_tests, to_polish_test_8);

  return s1;
}