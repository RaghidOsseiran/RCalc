#ifndef CALC
#define CALC


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned int uint;


char** postFixexp(char** exp);
int evaluationPostFix(char** exp);


/* utilitary functions */

bool checkOpToValRatio(char** exp);
void getSize(char** exp, int* size);
bool checkValidExpression(char** exp);
bool isOperator(char* x);
bool isNumber(char* x, uint numSize); // carefull numSize is the size of the number and NOT the expression.
bool checkDivByZero(char** exp);

#endif