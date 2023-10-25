#include "test.h"

START_TEST(parser_test_0) {
  int size = 0;
  token *parsed_str = parse_str("-2", &size);
  ck_assert_int_eq(size, 2);
  ck_assert_int_eq(parsed_str[0].code, UMINUS);
  ck_assert_int_eq(parsed_str[1].type, NUMBER);
  ck_assert_int_eq(parsed_str[1].value == 2.0, 1);

  free(parsed_str);
}
END_TEST

START_TEST(parser_test_1) {
  int size = 0;
  token *parsed_str = parse_str("3mod2", &size);
  ck_assert_int_eq(size, 3);
  ck_assert_int_eq(parsed_str[0].type, NUMBER);
  ck_assert_int_eq(parsed_str[0].value == 3.0, 1);
  ck_assert_int_eq(parsed_str[1].code, MOD);
  ck_assert_int_eq(parsed_str[2].type, NUMBER);
  ck_assert_int_eq(parsed_str[2].value == 2.0, 1);
  ck_assert_int_eq(parsed_str[3].type, VOID);

  free(parsed_str);
}
END_TEST

START_TEST(parser_test_2) {
  int size = 0;
  token *parsed_str = parse_str("2 -(x * sin(5))", &size);
  ck_assert_int_eq(size, 10);
  ck_assert_int_eq(parsed_str[0].type, NUMBER);
  ck_assert_int_eq(parsed_str[0].value == 2.0, 1);
  ck_assert_int_eq(parsed_str[1].code, MINUS);
  ck_assert_int_eq(parsed_str[2].type, BRACKET);
  ck_assert_int_eq(parsed_str[2].code, '(');
  ck_assert_int_eq(parsed_str[3].type, VAR);
  ck_assert_int_eq(parsed_str[4].type, OPERATION);
  ck_assert_int_eq(parsed_str[4].code, MULT);
  ck_assert_int_eq(parsed_str[5].type, FUNCTION);
  ck_assert_int_eq(parsed_str[5].code, SIN);

  free(parsed_str);
}
END_TEST

START_TEST(parser_test_3) {
  int size = 0;
  token *parsed_str = parse_str("2..02", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str(".202", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("202.", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  free(parsed_str);
}
END_TEST

START_TEST(parser_test_4) {
  int size = 0;
  token *parsed_str = parse_str("2+", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("+", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("sin", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("3x", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("sin+cos", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("sin+cos", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("2sin(2)", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("()", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("2+-3", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("1+2)2", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str(")2*3", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("*4", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("2*xsin(x)", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  parsed_str = parse_str("sos(x)", &size);
  ck_assert_int_eq(size, 0);
  ck_assert_int_eq(parsed_str == NULL, 1);

  free(parsed_str);
}
END_TEST

START_TEST(parser_test_5) {
  int size = 0;
  token *parsed_str = parse_str("x", &size);
  ck_assert_int_eq(size, 1);
  ck_assert_int_eq(parsed_str[0].type, VAR);

  free(parsed_str);
}
END_TEST

Suite *parser_test(void) {
  Suite *s1 = suite_create("parser tests");

  TCase *parser_tests = tcase_create("test 0");
  suite_add_tcase(s1, parser_tests);
  tcase_add_test(parser_tests, parser_test_0);
  tcase_add_test(parser_tests, parser_test_1);
  tcase_add_test(parser_tests, parser_test_2);
  tcase_add_test(parser_tests, parser_test_3);
  tcase_add_test(parser_tests, parser_test_4);
  tcase_add_test(parser_tests, parser_test_5);

  return s1;
}