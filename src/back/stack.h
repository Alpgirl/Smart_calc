#ifndef STACK_H_
#define STACK_H_

#include "token.h"
#define MAX_SIZE 255

typedef struct stack {
  int head;
  int size;
  token token_array[MAX_SIZE];
} stack;

stack stack_init(int size);
void stack_push(stack *stack, token elem);
token stack_pop(stack *stack);
token stack_top(stack *stack);
void stack_destroy(stack *stack);

#endif  // STACK_H_
