#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include<ctype.h>


struct Stack_t{
    unsigned int length;
    int top;
    int exp[101];
};

struct Stack_t* constructor(int length){
    struct Stack_t* stack = (struct Stack_t *)malloc(sizeof(struct Stack_t));
    stack->top = -1;
    stack->length = length;
    return stack;
}

int isStackEmpty(struct Stack_t *stack){
    if(stack->top == -1){
        return 1;
    }
    else return 0;
}

void push(struct Stack_t *stack, int operand){
    stack->exp[++stack->top] = operand;
}

int pop(struct Stack_t *stack){
    if(!isStackEmpty(stack))
        return stack->exp[stack->top--];
    else 
        return -1;
}

int calExp(int operand1, int operand2, char operator){
    switch(operator){
        case '+':
            return operand1+operand2;
        case '-':
            return operand2-operand1;
        case '*':
            return operand1*operand2;
        case '/':
            return operand2/operand1;
        default:
            return 0;
    }
}

int calPostFix(char* postfix){
    int result = -1;
    
    struct Stack_t *stack = constructor(strlen(postfix));
    if(stack == NULL)
        return result;
    
    result=0;
    
    for(int i = 0; i<strlen(postfix); i++ ){
        char element = postfix[i];
        if(element == ' ')
            continue;
        else if(isdigit(element)){
            int result = 0, j = i;
            while(isdigit(postfix[j]))
            {
                result = result * 10 + (postfix[j] - '0');
                j++;
            }
            i = j-1;
            push(stack, result);
        }
        else{
            int operand1 = pop(stack);
            int operand2 = pop(stack);
            if(operand1 == -1 || operand2 == -1)
                return 0;     
            
            result = calExp(operand1, operand2, postfix[i]);
            
            push(stack, result);
        }
    }
     return pop(stack);
}

int main() {

    char postfix[100];
    
    scanf("%[^\n]%*c", postfix);
    printf("%d",calPostFix(postfix));
    
    return 0;
}
