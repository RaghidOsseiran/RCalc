#include "Stack.h"


void errorHandler(char* msg){
    fprintf(stdout, "%s", msg);
    exit(EXIT_FAILURE);
}



Stack allocate_stack(uint size){
    Stack new_stack = malloc(sizeof(Stack_s));
    if (new_stack == NULL){ errorHandler("Heap allocation problem\n");}
    new_stack->content = malloc(size * sizeof(char*));
    if (new_stack->content == NULL){
        free(new_stack);
        errorHandler("Heap allocation problem for content array\n");
    }
    new_stack->size = size;
    new_stack->index_avail = 0;
    return new_stack;
};


void freeStack(Stack S){
    if (S != NULL){
        free(S->content);
    }
    free(S);
};


bool isEmptyStack(Stack S){
    if (S->index_avail == 0){
        return true;
    }
    return false;
};


char* val(Stack S){
    if (isEmptyStack(S)){ errorHandler("Cannot access the value of an empty stack\n");}
    return S->content[S->index_avail -1];
};


Stack depiller(Stack S){
    if (isEmptyStack(S)){ errorHandler("Cannot pop an already empty Stack\n");}
    S->index_avail -= 1;
    return S;
};


Stack empiller(Stack S, char* x){
    if (S->size == S->index_avail){
        S->content = realloc(S->content, (S->size * 2) * sizeof(char*));
        S->size = S->size * 2;
    }
    S->content[S->index_avail] = x;
    S->index_avail += 1;
    return S;
};

void printStack(Stack S){
    for(int i = 0 ; i < S->size; i++){
        printf("%s ", S->content[i]);
    }
    printf("\n");
}

