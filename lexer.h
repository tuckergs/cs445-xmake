
#ifndef LEXER_H_
#define LEXER_H_

#include <stdio.h>

#include "hash.h"
#include "Str.h"



void initlexer();
int _next_token();
void match(int);
int peek();
char* tok2str(int);

char * getcurtext();
void lineinfo();
void myassert(int,char*);

hash_t enttable;
int peekUsed;
char quoteused;
Str curtext;
Str curentitytext;
int curentityint;
int curtoken;
int curstate;

FILE* xmakefp;

int linenum;
int linecol;

#define NRM 0
#define EXPID 1
#define EXPATTR 2
#define EXPENT 3
#define EXPENT2 4
#define EXPCENT 5
#define EXPCENT2 6
#define EXPCXENT 7
#define EXPCXENT2 8
#define EXPENDQUOTE 9


#define ID 256
#define ATTRSTR 257

#endif // LEXER_H_

