#ifndef PARSER_H_
#define PARSER_H_

#include <stdlib.h>
#include <string.h>

#include "token.h"

#define MAX_INPUT_LENGTH 255
#define ERROR_INCORRECT_INPUT 1

token *parse_str(char *str, int *array_idx);
token parse_to_token(char **str, int *e_flag);
int is_digit(char c);
char *cut_number_from_str(char *start, char *end);
void check_number(char **number_str);
token parse_function_to_token(char **str, int *e_flag);
void make_function_token(token *function, int type, int code, int priority, int associativity);
void mark_unary(token *func, int array_idx, token *token_array);

void check_valid_expression(token *token_array, int *e_flag);
#endif  // PARSER_H_