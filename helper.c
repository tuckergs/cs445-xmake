#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "helper.h"


int ctoi(char c)
{
  if( ('0' <= c) && (c <= '9') ) return c - '0';
  else if( ('a' <= c) && (c <= 'f') ) return c - 'a' + 0xA;
  else if( ('A' <= c) && (c <= 'F') ) return c - 'A' + 0xA;
  else
  {
    fprintf(stderr,"Invalid input to ctoi\n");
    assert(0);
  }
}

int isValid(char c)
{
  if( (0x20 <= c) && (c <= 0x7E) )
    return 1;
  switch(c)
  {
    case '\n':
    case '\r':
    case '\t':
      return 1;
    default:
      return 0;
  }
}

int isNameStartChar(char c)
{
  if( isalpha(c) )
    return 1;
  if( (c == ':') || (c == '_') )
    return 1;
  return 0;

}

int isNameChar(char c)
{
  if( isNameStartChar(c) )
    return 1;
  if( isdigit(c) )
    return 1;
  if( (c == '-') || (c == '.') )
    return 1;
  return 0;
}

int isQuote(char c)
{
  if( (c == '\'') || (c == '\"') )
    return 1;
  return 0;
}
