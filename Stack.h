//
//  myStack.h
//  Stack
//
//  Created by Yijun Jiang on 5/6/17.
//  Copyright © 2017 Yijun Jiang. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include <stdio.h>

struct Stack{
    int size;
    char** array;
    char* top;
};


void init(struct Stack*);
int isempty(struct Stack);
char* pop(struct Stack*);
void push(struct Stack*, char*);

void print_stack(struct Stack);
void print_top(struct Stack);
void freeStack(struct Stack*);

#endif /* Stack_h */
