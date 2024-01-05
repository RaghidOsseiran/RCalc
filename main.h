#ifndef CALC
#define CALC


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int uint;


char** toPostFixexp(char** exp);
int evaluationPostFix(char** exp);


typedef enum Priorities{
    O = 0, // O for opening
    P = 1, // P for Plus
    M = 1, // M for minus
    T = 2, // T for times
    D = 2 // D for division
} Priorities;

/* utilitary functions */

bool checkOpToValRatio(char** exp);
bool checkValidParenthathese(char** exp, uint size);
bool checkPriority(char* v1, char* v2);
void getSize(char** exp, uint* size);
bool checkValidExpression(char** exp);
bool isOperator(char* x);
bool isNumber(char* x, uint numSize); // carefull numSize is the size of the number and NOT the expression.
bool checkDivByZero(char** exp);

#endif