#include "calc.h"

#include <stdio.h>

double calc(token *postfix, double var_value, int size) {
  double result = 0;

  if (!postfix) {
    result = NAN;
  } else {
    stack calculation_stack = stack_init(size);

    token top = *(postfix);

    while (top.type != VOID) {
      if (top.type == NUMBER) {
        stack_push(&calculation_stack, top);
      } else if (top.type == VAR) {
        token var = {0};
        var.type = NUMBER;
        var.value = var_value;
        stack_push(&calculation_stack, var);
      } else if (top.type == OPERATION) {
        double num2 = stack_pop(&calculation_stack).value;
        double num1 = stack_pop(&calculation_stack).value;

        double res = 0;

        switch (top.code) {
          case POW:
            res = pow(num1, num2);
            break;
          case DIV:
            res = num1 / num2;
            break;
          case MULT:
            res = num1 * num2;
            break;
          case MOD:
            res = fmod(num1, num2);
            break;
          case PLUS:
            res = num1 + num2;
            break;
          case MINUS:
            res = num1 - num2;
            break;
          default:
            break;
        }
        token result = {0};
        result.type = NUMBER;
        result.value = res;

        stack_push(&calculation_stack, result);
      } else if (top.type == FUNCTION) {
        double num = stack_pop(&calculation_stack).value;
        double res = 0;

        switch (top.code) {
          case COS:
            res = cos(num);
            break;
          case SIN:
            res = sin(num);
            break;
          case TAN:
            res = tan(num);
            break;
          case ACOS:
            res = acos(num);
            break;
          case ASIN:
            res = asin(num);
            break;
          case ATAN:
            res = atan(num);
            break;
          case SQRT:
            res = sqrt(num);
            break;
          case LN:
            res = log(num);
            break;
          case LOG:
            res = log10(num);
            break;
          case UMINUS:
            res = -num;
            break;
          case UPLUS:
            res = num;
            break;
          default:
            break;
        }
        token result = {0};
        result.type = NUMBER;
        result.value = res;

        stack_push(&calculation_stack, result);
      }

      top = *(postfix++);
    }

    result = stack_pop(&calculation_stack).value;

    stack_destroy(&calculation_stack);

    if (isinf(result)) {
      result = NAN;
    }
  }
  return result;
}