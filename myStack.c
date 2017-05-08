//
//  myStack.c
//  Stack
//
//  Created by Yijun Jiang on 5/6/17.
//  Copyright © 2017 Yijun Jiang. All rights reserved.
//

#include "myStack.h"
#include <stdlib.h>

extern char *strdup(const char *s);


void init(struct Mystack *stack){
    stack->size=0;
    stack->array = (char**)malloc(sizeof(char*)*(stack->size));
}


int isempty(struct Mystack stack){
    return stack.size==0 ? 1 : 0;
}


void push(struct Mystack *stack, char* str){
    stack->array = realloc(stack->array, sizeof(char*)*(stack->size+1));
    stack->array[stack->size]=strdup(str);
    stack->top = strdup(str);
    stack->size++;
}


char* pop(struct Mystack *stack){
    if (isempty(*stack)) {
        printf("empty stack can't be poped\n");
        return NULL;
    }
    char* top = stack->top;
    stack->array = realloc(stack->array, sizeof(char*)*(stack->size-1));
    stack->size--;
    if (isempty(*stack)) stack->top=NULL;
    else stack->top = strdup(stack->array[stack->size-1]);
    return top;
}



void print_top(struct Mystack stack){
    if (isempty(stack)) return;
    printf("%s\n",stack.top);
}


void print_stack(struct Mystack stack){
    if (isempty(stack)) return;
    for (int i=stack.size-1; i>=0; --i) {
        printf("%s\n",stack.array[i]);
    }
    //printf("\n");
}


void freeStack(struct Mystack *stack){
    free(stack->array);
    stack->top=NULL;
    stack->size=0;
}