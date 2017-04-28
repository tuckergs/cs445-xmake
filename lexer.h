
#ifndef LEXER_H_
#define LEXER_H_


#define IN stdin


int initlexer();
int _next_token();
void match(int);
int peek();
char* tok2str(int);

char * gettext();

extern int peekUsed;
extern Str curtext;
extern Str curentitytext;
extern int curtoken;

#define TOP 0
#define EXPID 1
#define EXPATTR 2
#define EXPENT 3
#define EXPENT2 4
#define EXPCENT 5
#define EXPCENT2 6
#define EXPCXENT 7
#define EXPCXENT2 8
#define TOP 9
#define TOP 10


#endif // LEXER_H_

