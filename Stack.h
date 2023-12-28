#ifndef STACK
#define STACK

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define INIT_SIZE 20


/*
* -> content containts the full expression weither it is valid or not, it is an array of char* and i chose this implementation over
* just a simple array of characters just so i could use bigger number and calculate bigger expressions.
* -> size is just the default beginning size of the stack, and if we reach the max size and try to use the push function
* we reallocate the space for 2 * (the original size of content)
* -> index_avail is just the index of the next available entry in the stack.
*/


struct Stack_s {
    char**  content;
    int size;
    int index_avail;
};

typedef struct Stack_s Stack_s;
typedef Stack_s* Stack;
typedef unsigned int uint;


Stack allocate_stack(uint size);
bool isEmptyStack(Stack S);
char* val(Stack S);
Stack depiller(Stack S);
Stack empiller(Stack S, char* x);
void freeStack(Stack S);


#endif 