#include "stack.h"

stack stack_init(int size) {
  stack stack = {0};

  stack.size = size;
  stack.head = 0;

  return stack;
}

void stack_push(stack *stack, token elem) {
  if (stack->head < stack->size) {
    stack->token_array[stack->head] = elem;
    stack->head += 1;
  }
}

token stack_pop(stack *stack) {
  token elem = {0};

  if (stack->head > 0) {
    elem = stack->token_array[stack->head - 1];
    stack->head -= 1;
  }

  return elem;
}

token stack_top(stack *stack) {
  token elem = {0};

  if (stack->head > 0) {
    elem = stack->token_array[stack->head - 1];
  }

  return elem;
}

void stack_destroy(stack *stack) {
  stack->size = 0;
  stack->head = 0;
}