#include "main.h"
#include "Stack.h"


void errorHandler(char* msg){
    fprintf(stdout, "%s", msg);
    exit(EXIT_FAILURE);
}


bool isOperator(char* x){
    if (x[0] == '+' || x[0] == '-' || x[0] == '*' || x[0] == '/'){
        return true;
    }
    return false;
}

bool isNumber(char* x, uint numSize){
    for (int i = 0 ; i < numSize-1; i++){ // numSize-1 so we dont check the \0 character
        if (x[i] < '0' || x[i] > '9') return false;
    }
    return true;
}

void getSize(char** exp, int* size){
    int cpt = 0;
    char** tmp = exp;
    while (tmp != NULL){
        cpt ++;
        tmp = tmp+1;
    }
    *size = cpt;
}

bool checkOpToValRatio(char** exp){
    int size;
    getSize(exp, &size);
    int numCount = 0;
    int opCount = 0;
    for(int i = 0 ; i < size; i++){
        uint inSize = strlen(exp[i])+1;
        if (isNumber(exp[i], inSize)){
            numCount++;
        }
        else if (isOperator(exp[i])){
            opCount++;
        }
    }
    return numCount > opCount;
}

bool checkDivByZero(char** exp){
    bool retVal = false;
    int size;
    getSize(exp, &size);
    char* end;
    Stack S = allocate_stack(INIT_SIZE);
    for(int i = 0; i < size; i++){
        S = empiller(S, exp[i]);
    }
    while(!isEmptyStack(S)){
        char* tmpVal = val(S);
        if (tmpVal[0] == '0') {
            S = depiller(S);
            char* tmpVal2 = val(S);
            if (tmpVal2[0] == '/'){ 
                retVal = true; 
                S = empiller(S, tmpVal);
                break;
            }
        }
        S = depiller(S);
    }
    freeStack(S);
    return retVal;
}



bool checkValidExpression(char** exp){
    if (exp == NULL){ errorHandler("Invalid Expression\n");}
    uint size = strlen(exp) + 1; // the + 1 is to take into account the \0 character at the end of the expression
    if (size <= 1){ errorHandler("Invalid Expression, to little characters\n");}
    if (isOperator(exp[0])){ errorHandler("Expression cannot start with an operator\n");} 
    if (checkOpToValRatio(exp) == false) return false;
    if (checkDivByZero(exp)) return false;
    return true;
};




char** postFixexp(char** exp){};
int evaluationPostFix(char** exp){};


