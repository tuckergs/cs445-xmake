
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"
#include "lexer.h"
#include "parser.h"

extern FILE* xmakefp;
extern char* targetname;
extern struct Stack revcmdstack;
extern struct Stack cmdstack;

int main(int argc, char** argv)
{

  //Set target name
  if (argc==1) {
    targetname="all";
  }
  else if (argc==2) {
    targetname=strdup(argv[1]);
    printf("\ntarget name: %s\n",targetname);
  }
  else
  {
    fprintf(stderr,"Must have zero or one arguments\n");
    exit(EXIT_FAILURE);
  }

  //Open XMakefile
  xmakefp = fopen("XMakefile","r");

  //Initialize stacks
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
    fprintf(stderr,"%s\n",cmd);
    FILE * fp = popen(cmd, "r");
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      printf("%s", path);
    }
    pclose(fp);

  }
}
