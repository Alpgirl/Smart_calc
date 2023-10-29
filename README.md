# Smart_calc
Smart calculator is dedicated to compute arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.)

## Quickstart
Guide how to build, run, and use in your applications.

### Build

| command          | purpose                               |
|-                 |-                                      |
| make [all]       | build library calc.a and run tests    |
| make calc.a      | build library calc.a                  |
| make test        | run unit tests                        |
| make gcov_report | generate test coverage HTML report    |
| make codestyle   | apply google codestyle in project     |
| make run         | build and run command line calculator |

### Include in other applications

You can use static library _calc.a_ to parse and evaluate `char*` and `char[]` math expression in C/C++ programs.

Evaluating an expression has the following structure:

```
char expr[] = "Your expression here";
double var = 0;

int size = 0;

token *infix = parse_str(expr, &size);
token *postfix = to_polish(infix, size);
double res = calc(postfix, var, size);

free(infix);
free(postfix);
```

There are 3 main steps in calculating expression and 3 functions which provide these steps:
|                                                            |                                                                 |
|-                                                           |-                                                                |
| `token *parse_str(char *str, int *array_idx)`              | parse input string expression                                   |
| `token *to_polish(token *infix_array, int length)`         | transform parsed expression into reverse polish notation (RPN)  |
| `double calc(token *postfix, double var_value, int size)`  | evaluate RPN expression                                         |

In case of any error `calc()` returns _nan_.

To build your application with _calc.a_ library you have to:

1. build library `make calc.a`
1. include `calc.h` header file in your program
1. build your program with `calc.a` as src file, e.g. `gcc <your_program> calc.a` 
(on some systems `-lm` flag should also be specified)

### Supported syntax

Arithmetic expressions in infix notation support the following arithmetic operations and mathematical functions:

- **Arithmetic operators**:

| Operator name | Infix notation <br /> (Classic) |
| --------- | ------ |
| Brackets | (a + b) |
| Addition | a + b |
| Subtraction | a - b |
| Multiplication | a * b |
| Division | a / b |
| Power | a ^ b |
| Modulus | a mod b |
| Unary plus | +a |
| Unary minus | -a |

- **Functions**:
  
| Function description | Function |
| ------ | ------ |
| Computes cosine | cos(x) |
| Computes sine | sin(x) |
| Computes tangent | tan(x) |
| Computes arc cosine | acos(x) |
| Computes arc sine | asin(x) |
| Computes arc tangent | atan(x) |
| Computes square root | sqrt(x) |
| Computes natural logarithm | ln(x) |
| Computes common logarithm | log(x) |


## Development instructions

The source code was decomposed into following logical blocks:

- `parser.c` - all functions with parsing purpose.
- `to_polish.c` - functions which are used while parsing input expression into RPN.
- `calc.c` - evaluating an RPN expression.
- `stack.c` - simplified implementation of stack. Simplification is based on limitation max input expression length on 255 symbols.

Ideas for modification the project:
1. modification of stack that provides processing longer expressions;
1. make more detailed output in case of error occured. In current implementation only _nan_ is returned as the result. 
  