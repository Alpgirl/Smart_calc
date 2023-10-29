#ifndef CALC_H_
#define CALC_H_

#include <math.h>

#include "parser.h"
#include "stack.h"
#include "to_polish.h"

double calc(token *postfix, double var_value, int size);

#endif  // CALC_H_