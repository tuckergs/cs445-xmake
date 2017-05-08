
#include "main.h"

#include <stdio.h>
#include "lexer.h"
#include "parser.h"


int main()
{
  //Initialize the lexer
  initlexer();

  //Begin parsing
  document();

  //Execute commands
  execstack();

}
