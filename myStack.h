//
//  myStack.h
//  Stack
//
//  Created by Yijun Jiang on 5/6/17.
//  Copyright © 2017 Yijun Jiang. All rights reserved.
//

#ifndef myStack_h
#define myStack_h

#include <stdio.h>

struct Mystack{
    int size;
    char** array;
    char* top;
};


void init(struct Mystack*);
int isempty(struct Mystack);
char* pop(struct Mystack*);
void push(struct Mystack*, char*);

void print_stack(struct Mystack);
void print_top(struct Mystack);
void freeStack(struct Mystack*);

#endif /* myStack_h */
