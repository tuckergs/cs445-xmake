
#include "main.h"

#include <stdio.h>
#include "lexer.h"
#include "parser.h"


int main(int argc, char** argv)
{

  init(&cmdstack);
  init(&revcmdstack);
  init(&tarstack);

  //Initialize the lexer
  initlexer();

  //Begin parsing
  document();

  //Put commands in an executable order
  revstacks();

  //Execute commands
  execstack();

}

void revstacks()
{
  while(!isempty(revcmdstack))
  {
    push(&cmdstack,pop(&revcmdstack));
  }
}

void execstack()
{
  while(!isempty(cmdstack))
  {
    system(pop(&cmdstack));
  }
}
