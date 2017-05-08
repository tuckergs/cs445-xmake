
#include "main.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"


int main(int argc, char** argv)
{

  if (argc==1) {
    targetname=strdup("all");
  }
  if (argc==2) {
    targetname=argv[1];
  }

  init(&cmdstack);
  init(&revcmdstack);
  init(&tarstack);

  //Initialize the lexer
  initlexer();

  //Begin parsing
  document();

  //Put commands in an executable order
  revstacks();

  //print cmds
  //print_stack(cmdstack);

  //Execute commands
  printf("\n");
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
    char path[1035];
    char* cmd = pop(&cmdstack);
    FILE * fp = popen(cmd, "r");
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      printf("%s", path);
    }
    pclose(fp);

  }
}
