# Smart_calc

Smart calculator is dedicated to compute arithmetic expressions by following the order, as well as some mathematical functions (sine, cosine, logarithm, etc.)

## Quickstart

Guide how to build, run, and use in your applications.

### Pipeline

To launch the application there are 3 shell scripts given: prereqs.sh, build.sh and test.sh.

Prereqs.sh:     installs GoogleTest library to provide tests for the application. \
Build.sh:       builds the project and launches it. \
Test.sh:        launches the tests.

You can launch everything inside docker container using Dockerfile by COMMAND.
It will set up the developing environment inside the container, run prereqs.sh, then build.sh, test.sh and eventually exit the container and delete it.

## For developers

If you want manually try the application use the following instructions.

### Prerequirements and tests

GoogleTest is required for the application. Using `./prereqs.sh` GTest is installed in the root directory.
Using `./test.sh` tests are launched.

### Build

To build the application you need to run `./build.sh {target}`.

As for {target}, there are options below:


| command   | purpose                               |
| ----------- | --------------------------------------- |
| calc.a    | build library calc.a                  |
| codestyle | apply google codestyle in project     |
| clean     | clean build files                     |
| run       | build and run command line calculator |

### Launching 

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


|                                                           |                                                                |
| ----------------------------------------------------------- | ---------------------------------------------------------------- |
| `token *parse_str(char *str, int *array_idx)`             | parse input string expression                                  |
| `token *to_polish(token *infix_array, int length)`        | transform parsed expression into reverse polish notation (RPN) |
| `double calc(token *postfix, double var_value, int size)` | evaluate RPN expression                                        |

In case of any error `calc()` returns _nan_.

To build your application with _calc.a_ library you have to:

1. build library `make calc.a`
2. include `calc.h` header file in your program
3. build your program with `calc.a` as src file, e.g. `gcc <your_program> calc.a`
   (on some systems `-lm` flag should also be specified)

### Supported syntax

Arithmetic expressions in infix notation support the following arithmetic operations and mathematical functions:

- **Arithmetic operators**:


| Operator name  | Infix notation<br /> (Classic) |
| ---------------- | -------------------------------- |
| Brackets       | (a + b)                        |
| Addition       | a + b                          |
| Subtraction    | a - b                          |
| Multiplication | a * b                          |
| Division       | a / b                          |
| Power          | a ^ b                          |
| Modulus        | a mod b                        |
| Unary plus     | +a                             |
| Unary minus    | -a                             |

- **Functions**:


| Function description       | Function |
| ---------------------------- | ---------- |
| Computes cosine            | cos(x)   |
| Computes sine              | sin(x)   |
| Computes tangent           | tan(x)   |
| Computes arc cosine        | acos(x)  |
| Computes arc sine          | asin(x)  |
| Computes arc tangent       | atan(x)  |
| Computes square root       | sqrt(x)  |
| Computes natural logarithm | ln(x)    |
| Computes common logarithm  | log(x)   |

## Development instructions

The source code was decomposed into following logical blocks:

- `parser.c` - all functions with parsing purpose.
- `to_polish.c` - functions which are used while parsing input expression into RPN.
- `calc.c` - evaluating an RPN expression.
- `stack.c` - simplified implementation of stack. Simplification is based on limitation max input expression length on 255 symbols.

Ideas for modification the project:

1. modification of stack that provides processing longer expressions;
2. make more detailed output in case of error occured. In current implementation only _nan_ is returned as the result.
