#ifndef TEST_H_
#define TEST_H_

#include <check.h>

#include "../back/calc.h"

Suite *parser_test(void);
Suite *to_polish_test(void);
Suite *calc_test(void);

#endif