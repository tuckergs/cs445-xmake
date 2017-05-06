
#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>

Str curtext;
Str curentitytext;
int peekUsed;
int curtoken;

void initlexer()
{
  peekUsed = 0;
}

void match(int tok)
{

  int ctoken;

  if(peekUsed)
    ctoken = curtoken;
  else
    ctoken = _next_token();

  if(ctoken != tok)
  {
    fprintf(stderr,"You broke it!\nYou created a syntax error!\nExpected: %s\nReceived: %s\n\n",tok2str(tok),tok2str(curtoken));
    assert(0);
  }
}

int peek()
{
  if(peekUsed)
    return curtoken;
  else
  {
    peekUsed = 1;
    return _next_token();
  }
}

char* tok2str(int tok)
{
  char* str;
  switch(tok)
  {
    case ID:
      return strdup("ID");
    case ATTRSTR:
      return strdup("ATTRSTR");
    default:
      str = malloc(4);
      sprintf(str,"\'%c\'",(char)tok);
      return str;
  }
}

char* gettext()
{
  return strdup(curtext->str);
}





//The epicness

int _next_token()
{
  curtext = Str_init();
  curentitytext = Str_init();
  char c;
//beginning
  while(1)
  {
    c = getc(stdin);
    myassert(isValid(c),"You broke it! Invalid character!\n");

    switch(curstate)
    {

    case NRM:
      if(isNameStartChar(c))
      {
        curtext = Str_clear();
        curtext = append(curtext,c);
        curstate = EXPID;
      }
      else if(isQuote(c))
      {
        quoteused = c;
        curtext = Str_clear();
      }
      else if(isSpace(c) || isWhitespace(c))
      {
      }
      else
      {
        return c;
      }
      break;
    case EXPID:
      if(isNameChar(c))
      {
        curtext = append(curtext,c);
      }
      else
      {
        ungetc(c,stdin);
        curstate = NRM;
        return ID;
      }
      break;
//TODO: More schtuff
  }
}
