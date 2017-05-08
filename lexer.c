
#include "lexer.h"

#include "hash.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

extern hash_t enttable;
extern Str curtext;
extern Str curentitytext;
extern int curentityint;
extern char quoteused;
extern int peekUsed;
extern int curtoken;
extern int curstate;

extern int linenum;
extern int linecol;

void initlexer()
{
  peekUsed = 0;
  curstate = NRM;
  linenum = 1;
  linecol = 1;
  hash_insert(&enttable,"lt",'<');
  hash_insert(&enttable,"gt",'>');
  hash_insert(&enttable,"amp",'&');
}

void match(int tok)
{

  int ctoken;

  if(peekUsed)
    ctoken = curtoken;
  else
    ctoken = _next_token();

  peekUsed = 0;

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

char* getcurtext()
{
  return strdup(curtext.str);
}

void lineinfo()
{
  fprintf(stderr,"Line %d,%d: ",linenum,linecol);
}

void myassert(int cond,char* msg)
{
  if(!cond)
  {
    lineinfo();
    fprintf(stderr,"%s\n",msg);
    exit(EXIT_FAILURE);
  }
}



//The epicness

int _next_token()
{
  curtext = Str_clear(curtext);
  curentitytext = Str_clear(curentitytext);
  char c;

  while(1)
  {
    c = getc(stdin);
    linecol++;
    if(c == '\n')
    {
      linenum++;
      linecol = 1;
    }
    myassert(isValid(c),"You broke it! Invalid character!");

    switch(curstate)
    {

    case NRM:
      if(isNameStartChar(c))
      {
        curtext = Str_clear(curtext);
        curtext = append(curtext,c);
        curstate = EXPID;
      }
      else if(isQuote(c))
      {
        quoteused = c;
        curtext = Str_clear(curtext);
        curstate = EXPATTR;
        return c;
      }
      else if(isspace(c))
      {
        //advance input
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
    case EXPATTR:
      myassert(c != '<',"\'<\' can't be used in quotes! Escape it using &lt;");
      if(c == quoteused)
      {
        ungetc(c,stdin);
        curstate = EXPENDQUOTE;
        return ATTRSTR;
      }
      if(c == '&')
      {
        curstate = EXPENT;
      }
      else
      {
        curtext = append(curtext,c);
      }
      break;
    case EXPENT:
      if(isNameStartChar(c))
      {
        curentitytext = Str_clear(curentitytext);
        curentitytext = append(curentitytext,c);
        curstate = EXPENT2;
      }
      else if(c == '#')
      {
        curstate = EXPCENT;
      }
      else
      {
        myassert(2 + 2 == 5,"Expected: A name or a #");
      }
      break;
    case EXPENT2:
      if(isNameChar(c))
      {
        curentitytext = append(curentitytext,c);
      }
      else if(c == ';')
      {
        char ch;
        node_t * chNode = hash_search(&enttable,curentitytext.str);
        myassert((chNode != NULL),"Entity not found");
        ch = chNode->chr;
        curtext = append(curtext,ch);
        curstate = EXPATTR;
      }
      else
      {
        myassert(841 == 29,"Expected: A name or \';\'");
      }
      break;
    case EXPCENT:
      if(isdigit(c))
      {
        curentityint = ctoi(c);
        curstate = EXPCENT2;
      }
      else if(c == 'x')
      {
        curstate = EXPCXENT;
      }
      else
      {
        myassert("Christino Tamon" == "Tino","Expected: A 8 bit number or \'x\'");
      }
      break;
    case EXPCENT2:
      if(isdigit(c))
      {
        curentityint = 10 * curentityint + ctoi(c);
      }
      else if(c == ';')
      {
        if(curentityint >= 256)
        {
          myassert("29" == "Perfect square","We can't do values over 255");
        }
        curentitytext = append(curentitytext,(char)curentityint);
        curstate = EXPATTR;
      }
      else
      {
        myassert(0,"Expected: An 8-bit number or \';\'");
      }
      break;
    case EXPCXENT:
      if(isxdigit(c))
      {
        curentityint = ctoi(c);
        curstate = EXPCXENT2;
      }
      else{
        myassert(0,"Expected hexadecimal digit");
      }
      break;
    case EXPCXENT2:
      if(isxdigit(c))
      {
        curentityint = 16 * curentityint + ctoi(c);
      }
      else if(c == ';')
      {
        if(curentityint >= 256)
        {
          myassert("841"=="Perfect square","We can't do values over 0xFF");
        }
        curentitytext = append(curentitytext,(char)curentityint);
        curstate = EXPATTR;
      }
      else
      {
        myassert(1912 == 3,"Expected hexademical digit or \';\'");
      }
      break;
    case EXPENDQUOTE:
      if(isQuote(c))
      {
        curstate = NRM;
        return c;
      }
      else
      {
        myassert("Bill Gates favorite color" == "twelve","If you get this error message, YOU BROKE IT!!!\nYou are probably malicious person.\nYou poor soul.");
      }
    default:
      myassert("bagel" == "twelve","If you are seeing this message, there could be one of three reasons:\n\n\t1: You broke it.\n\t2: You broke it.\n\t3: YOU BROKE IT!\n\nYou fail it!\nYour skill is not enough...\nGoodbye!\n\nAlso, you are probably malicious. You poor soul.");
      break;
    }
  }
}
