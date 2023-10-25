#ifndef TO_POLISH_H_
#define TO_POLISH_H_

#include "parser.h"
#include "stack.h"
#include "token.h"

token *to_polish(token *infix_array, int length);

#endif  // POLISH_H_