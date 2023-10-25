#ifndef TOKEN_H_
#define TOKEN_H_

/* TOKEN TYPES */
#define VOID 0
#define NUMBER 1
#define FUNCTION 2
#define OPERATION 3
#define BRACKET 4
#define VAR 5

/* TOKEN CODES */
#define COS 'c'
#define SIN 's'
#define TAN 't'
#define ACOS 'C'
#define ASIN 'S'
#define ATAN 'T'
#define SQRT 'R'
#define LN 'l'
#define LOG 'L'

#define MINUS 'm'
#define UMINUS 'M'
#define PLUS 'p'
#define UPLUS 'P'
#define MULT '*'
#define DIV '/'
#define POW '^'
#define MOD 'd'

/* OPERATION PRIORITY */
#define HIGH 10
#define MEDIUM 5
#define LOW 1

/* OPERATION ASSOCIATIVITY*/
#define LEFT 1
#define RIGHT 2

typedef struct token {
  int type;
  char code;
  double value;
  int priority;
  int associativity;
} token;

#endif  // TOKEN_H_