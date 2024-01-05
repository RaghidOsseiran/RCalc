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

void getSize(char** exp, uint* size){
    uint cpt = 0;
    char** tmp = exp;
    while (tmp != NULL){
        cpt ++;
        tmp = tmp+1;
    }
    *size = cpt;
}



bool checkOpToValRatio(char** exp){
    uint size = 0;
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
    uint size = 0;
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
            if (!isEmptyStack(S)){
                char* tmpVal2 = val(S);
                if (tmpVal2[0] == '/'){ 
                    retVal = true; 
                    S = empiller(S, tmpVal);
                    break;
                }
            }
        }
        S = depiller(S);
    }
    freeStack(S);
    return retVal;
}

bool checkValidParenthathese(char** exp, uint size){
    if (exp == NULL) return false;
    Stack S = allocate_stack(INIT_SIZE);
    for(int i = 0; i < size; i++){
        if (exp[i][0] == '('){
            S = empiller(S, exp[i]);
        } else if (exp[i][0] == ')'){
            if (isEmptyStack(S)) return false;
            S = depiller(S);
        }
    }
    if (!isEmptyStack(S)) return false;
    return true;
}



bool checkValidExpression(char** exp){
    if (exp == NULL){ errorHandler("Invalid Expression\n");}
    uint size = strlen(exp);
    if (size <= 1){ errorHandler("Invalid Expression, to little characters\n");}
    if (isOperator(exp[0])){ errorHandler("Expression cannot start with an operator\n");} 
    if (checkOpToValRatio(exp) == false) return false;
    if (checkDivByZero(exp)) return false;
    if (!checkValidParenthathese(exp, size)) return false;
    return true;
}

bool checkPriority(char* v1, char* v2){
    if (v1 == NULL || v2 == NULL) return false;
    Priorities val1;
    Priorities val2;
    switch(v1[0]){
        case '+': val1 = P; break;
        case '*': val1 = T; break;
        case '-': val1 = M; break;
        case '/': val1 = D; break;
        default: return false;
    }
    switch(v2[0]){
        case '+': val2 = P; break;
        case '*': val2 = T; break;
        case '-': val2 = M; break;
        case '/': val2 = D; break;
        default: return false;
    }
    if (val1 >= val2) return true;
    return false;
}


char** toPostFixexp(char** exp){
    if (exp == NULL) return NULL;
    uint expSize = 0;
    getSize(exp, &expSize);
    Stack S = allocate_stack(expSize+2);
    char** res = (char**)malloc(expSize * sizeof(char*));
    int j = 0;
    for(int i = 0; i < expSize; i++){
        uint inSize = strlen(exp[i])+1;
        if (isNumber(exp[i], inSize)){
            res[j] = malloc(inSize * sizeof(char));
            strcpy(res[j], exp[i]);
            j++;
        } else if (exp[i][0] == '('){
            S = empiller(S, exp[i]);
        } else if (exp[i][0] == ')'){
            while(!isEmptyStack(S) && (val(S))[0] != '('){
                res[j] = malloc(inSize * sizeof(char));
                char* value = val(S);
                strcpy(res[j], value);
                S = depiller(S);
                j++;
            }
            S = depiller(S); // to remove the '('
        } else {
            while(!isEmptyStack(S) && checkPriority(val(S), exp[i])){
                res[j] = malloc(inSize * sizeof(char));
                strcpy(res[j], val(S));
                S = depiller(S);
                j++;
            }
            S = empiller(S, exp[i]);
        }
    }
    while(!isEmptyStack(S)){
        uint size = strlen(val(S)) + 1;
        res[j] = malloc(size * sizeof(char));
        strcpy(res[j], val(S));
        j++;
        S = depiller(S);
    }
    return res;
}



int evaluationPostFix(char** exp){};


