#include "parser.h"

#include <stdio.h>

token *parse_str(char *str, int *array_idx) {
  int length_str = strlen(str);
  int e_flag = 0;

  if (length_str > MAX_INPUT_LENGTH) {
    e_flag = ERROR_INCORRECT_INPUT;
  }

  token *token_array = (token *)calloc(MAX_INPUT_LENGTH, sizeof(token));
  *array_idx = 0;

  // parsing string into array of tokens
  while (!e_flag && *str) {
    token processed_token = parse_to_token(&str, &e_flag);
    // check unary '+' and '-'
    if (processed_token.code == MINUS || processed_token.code == PLUS) {
      mark_unary(&processed_token, *array_idx, token_array);
    }
    if (processed_token.type) {
      token_array[(*array_idx)++] = processed_token;
    }
  }

  if (!e_flag) {
    check_valid_expression(token_array, &e_flag);
  }

  if (e_flag == ERROR_INCORRECT_INPUT) {
    free(token_array);
    token_array = NULL;
    *array_idx = 0;
  }

  return token_array;
}

token parse_to_token(char **str, int *e_flag) {
  token processed_token = {0};

  char symbol = **str;
  if (is_digit(symbol)) {
    char *start = *str;

    while (**str && is_digit(**str)) {
      (*str)++;
    }

    char *number_str =
        cut_number_from_str(start, *str);  // NULL or valid number

    if (number_str) {
      double number = atof(number_str);
      processed_token.type = NUMBER;
      processed_token.value = number;
      free(number_str);
    } else {
      *e_flag = ERROR_INCORRECT_INPUT;
    }
  } else if (symbol == '(' || symbol == ')') {
    *(str) += 1;
    processed_token.type = BRACKET;
    processed_token.code = symbol;
  } else if (symbol == 'x') {
    *(str) += 1;
    processed_token.type = VAR;
    processed_token.code = symbol;
  } else if (symbol == ' ') {
    *(str) += 1;
  } else {
    processed_token = parse_function_to_token(str, e_flag);
  }

  return processed_token;
}

int is_digit(char c) { return ((c >= '0' && c <= '9') || c == '.'); }

char *cut_number_from_str(char *start, char *end) {
  char *number_str = (char *)calloc(end - start + 1, sizeof(char));

  if (number_str) {
    char *ptr_number_str = number_str;
    while (start < end) {
      *(ptr_number_str++) = *(start++);
    }
    check_number(&number_str);
  }

  return number_str;
}

void check_number(char **number_str) {
  char *ptr = *(number_str);
  int error_flag = 0;

  // first digit is not '.'
  if (*ptr == '.') {
    error_flag = 1;
  }

  // there is no more than one '.' in number
  int dots_amount = 0;
  while (*(ptr)) {
    if (*ptr == '.') {
      dots_amount++;
    }
    ptr++;
  }
  if (dots_amount > 1) {
    error_flag = 1;
  }

  // last digit is not '.'
  if (*(ptr - 1) == '.') {
    error_flag = 1;
  }

  if (error_flag) {
    free(*number_str);
    *number_str = NULL;
  }
}

token parse_function_to_token(char **str, int *e_flag) {
  token parsed_function = {0};
  if (**str == '-') {
    make_function_token(&parsed_function, OPERATION, MINUS, LOW, LEFT);
    *(str) += 1;
  } else if (**str == '+') {
    make_function_token(&parsed_function, OPERATION, PLUS, LOW, LEFT);
    *(str) += 1;
  } else if (**str == '*') {
    make_function_token(&parsed_function, OPERATION, MULT, MEDIUM, LEFT);
    *(str) += 1;
  } else if (**str == '/') {
    make_function_token(&parsed_function, OPERATION, DIV, MEDIUM, LEFT);
    *(str) += 1;
  } else if (**str == '^') {
    make_function_token(&parsed_function, OPERATION, POW, HIGH, RIGHT);
    *(str) += 1;
  } else if (strstr(*str, "ln") == *str) {
    make_function_token(&parsed_function, FUNCTION, LN, HIGH, RIGHT);
    *(str) += 2;
  } else if (strstr(*str, "log") == *str) {
    make_function_token(&parsed_function, FUNCTION, LOG, HIGH, RIGHT);
    *(str) += 3;
  } else if (strstr(*str, "mod") == *str) {
    make_function_token(&parsed_function, OPERATION, MOD, MEDIUM, LEFT);
    *(str) += 3;
  } else if (strstr(*str, "cos") == *str) {
    make_function_token(&parsed_function, FUNCTION, COS, HIGH, RIGHT);
    *(str) += 3;
  } else if (strstr(*str, "sin") == *str) {
    make_function_token(&parsed_function, FUNCTION, SIN, HIGH, RIGHT);
    *(str) += 3;
  } else if (strstr(*str, "tan") == *str) {
    make_function_token(&parsed_function, FUNCTION, TAN, HIGH, RIGHT);
    *(str) += 3;
  } else if (strstr(*str, "acos") == *str) {
    make_function_token(&parsed_function, FUNCTION, ACOS, HIGH, RIGHT);
    *(str) += 4;
  } else if (strstr(*str, "asin") == *str) {
    make_function_token(&parsed_function, FUNCTION, ASIN, HIGH, RIGHT);
    *(str) += 4;
  } else if (strstr(*str, "atan") == *str) {
    make_function_token(&parsed_function, FUNCTION, ATAN, HIGH, RIGHT);
    *(str) += 4;
  } else if (strstr(*str, "sqrt") == *str) {
    make_function_token(&parsed_function, FUNCTION, SQRT, HIGH, RIGHT);
    *(str) += 4;
  }

  if (parsed_function.type == VOID) {
    *e_flag = ERROR_INCORRECT_INPUT;
  }

  return parsed_function;
}

void make_function_token(token *function, int type, int code, int priority, int associativity) {
  function->type = type;
  function->code = code;
  function->priority = priority;
  function->associativity = associativity;
}

void mark_unary(token *func, int array_idx, token *token_array) {
  if (array_idx == 0 || token_array[array_idx - 1].code == '(') {
    func->type = FUNCTION;
    switch (func->code) {
      case MINUS:
        func->code = UMINUS;
        break;
      case PLUS:
        func->code = UPLUS;
        break;
      default:
        break;
    }
  }
}

void check_valid_expression(token *token_array, int *e_flag) {
  token prev = {0};
  token next = *(token_array++);

  while (next.type != VOID) {
    switch (prev.type) {
      case VOID:
        if (next.type == OPERATION || next.code == ')') {
          *e_flag = ERROR_INCORRECT_INPUT;
        }
        break;
      case NUMBER:
        if (next.type == FUNCTION || next.type == VAR || next.code == '(') {
          *e_flag = ERROR_INCORRECT_INPUT;
        }
        break;
      case VAR:
        if (next.type == FUNCTION || next.type == VAR || next.code == '(' ||
            next.type == NUMBER) {
          *e_flag = ERROR_INCORRECT_INPUT;
        }
        break;
      case FUNCTION:
        if (next.type == OPERATION || next.code == ')') {
          *e_flag = ERROR_INCORRECT_INPUT;
        }
        break;
      case OPERATION:
        if (next.type == OPERATION || next.code == ')') {
          *e_flag = ERROR_INCORRECT_INPUT;
        }
        break;
      case BRACKET:
        if (prev.code == '(') {
          if (next.type == OPERATION || next.code == ')') {
            *e_flag = ERROR_INCORRECT_INPUT;
          }
        } else {
          if (next.type == NUMBER || next.type == FUNCTION ||
              next.type == VAR || next.code == '(') {
            *e_flag = ERROR_INCORRECT_INPUT;
          }
        }
        break;
      default:
        break;
    }

    prev = next;
    next = *(token_array++);
  }

  if (prev.type == VOID || prev.type == FUNCTION || prev.type == OPERATION ||
      prev.code == '(') {
    *e_flag = ERROR_INCORRECT_INPUT;
  }
}