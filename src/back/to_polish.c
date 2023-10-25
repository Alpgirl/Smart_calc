#include "to_polish.h"

token *to_polish(token *infix_array, int length) {
  int e_flag = 0;

  if (!infix_array) {
    e_flag = ERROR_INCORRECT_INPUT;
  }

  stack pending_operations = stack_init(length);
  token *postfix_array = (token *)calloc(length + 1, sizeof(token));
  token *ptr_postfix_array = postfix_array;

  for (int idx = 0; idx < length && !e_flag; idx++) {
    token elem = infix_array[idx];

    if (elem.type == NUMBER) {
      *(ptr_postfix_array++) = elem;
    } else if (elem.type == VAR) {
      *(ptr_postfix_array++) = elem;
    } else if (elem.code == '(') {
      stack_push(&pending_operations, elem);
    } else if (elem.type == FUNCTION) {
      stack_push(&pending_operations, elem);
    } else if (elem.type == OPERATION) {
      token top = stack_top(&pending_operations);

      while (top.priority > elem.priority ||
             (top.priority == elem.priority && elem.associativity == LEFT)) {
        stack_pop(&pending_operations);
        *(ptr_postfix_array++) = top;
        top = stack_top(&pending_operations);
      }

      stack_push(&pending_operations, elem);
    } else if (elem.code == ')') {
      token top = stack_top(&pending_operations);

      while (top.code != '(' && top.type != VOID) {
        stack_pop(&pending_operations);
        *(ptr_postfix_array++) = top;
        top = stack_top(&pending_operations);
      }

      if (top.type == BRACKET) {
        stack_pop(&pending_operations);  // delete bracket
        top = stack_top(&pending_operations);

        if (top.type == FUNCTION) {
          stack_pop(&pending_operations);
          *(ptr_postfix_array++) = top;
        }
      } else {
        e_flag = ERROR_INCORRECT_INPUT;
      }
    }
  }

  if (!e_flag) {
    token top = stack_top(&pending_operations);
    while (top.type && !e_flag) {
      if (top.type == BRACKET) {
        e_flag = ERROR_INCORRECT_INPUT;
      } else {
        stack_pop(&pending_operations);
        *(ptr_postfix_array++) = top;
      }

      top = stack_top(&pending_operations);
    }
    *(ptr_postfix_array++) = top;
  }

  if (e_flag) {
    free(postfix_array);
    postfix_array = NULL;
  }

  stack_destroy(&pending_operations);

  return postfix_array;
}