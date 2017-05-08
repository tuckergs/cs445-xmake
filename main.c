#include <stdio.h>
#include "lexer.h"
#include "parser.h"


int main()
{
  initlexer();
  document();

  /*
  while(1)
  {
    int tok = _next_token();
    if(tok <= 255)
      fprintf(stderr,"{\'%c\'}",(char)tok);
    else
      fprintf(stderr,"{%s: %s}",tok2str(tok),getcurtext());

  }
  */
}
