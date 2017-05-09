#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"
#include "Stack.h"
#include "main.h"

//peek(): check next token without match it
int check_file = 0;
int push_cmd = 0;
int push_tar = 0;
extern char* targetname;
extern struct Stack tarstack,revcmdstack;



//document: '<' document2
void document(){
  //TODO fix
  match('<');// less than should be toekn
  document2();
}



/*
   document2: '?' XML attributes '?' '>' root
   | root2
*/
void document2(){
  if(peek()=='?'){
    match('?');
    match(ID);
    myassert(!strcmp(getcurtext(),"xml"),"Expected \"xml\"");
    attributes();
    match('?');
    match('>');
    root();
  }else{
    root2();
  }
}



/* attributes: ID attribute2 attributes
   |  empty
*/
void attributes(){
  if(peek()==ID){
    match(ID);
    attribute2();
    attributes();
  }
}


//attribute2: '=' '\"' ATTRSTR '\"'
void attribute2(){
  match('=');
  match('\"');
  match(ATTRSTR);

  char* s = getcurtext();
  //printf("\n%s\n",s);
  if (check_file) {
    if (access(s, F_OK) == -1){
      printf("\n%s\n",s);
      myassert( 0, "file not exists");
    }
  }
  else if (push_cmd && (strcmp(s,targetname)==0 || strcmp("all",targetname)==0)) {
    push(&revcmdstack,s);
  }else if (push_tar){
    push(&tarstack,s);
  }

  match('\"');
}


//root: '<' root2
void root(){
  match('<');
  root2();
}


//root2: begintag2 childswithend
void root2(){
  begintag2();
  childswithend();
}


//begintag2: ID attributes '>'
void begintag2(){
  match(ID);
  attributes();
  match('>');
}



//childswithend: '<' childswithend2
//  | TEXTSTR childswithend
void childswithend(){
  match('<');
  childswithend2();
}



//childswithend2: ID tagelement3 childswithend
//  | endtag2
void childswithend2(){
  if(peek()==ID){
    match(ID);

    //deal with dependency
    char* s=getcurtext();
    //printf("\n%s\n",s);
    if (strcmp(s,"dependency")==0) {
      check_file = 1;
    }
    else if (strcmp(s,"command")==0) {
      push_cmd = 1;
    }
    else if (strcmp(s,"target")==0){
      push_tar = 1;
    }

    tagelement3();
    childswithend();
  }else{
    endtag2();
  }
}


//endtag2: '/' ID '>'
void endtag2(){
  match('/');
  match(ID);

  char* s=getcurtext();
  //printf("\n%s\n",s);

  if (strcmp(s,"target")==0) {
    pop(&tarstack);
    push_tar = 0;
  }

  match('>');
}



//tagelement3: attributes tagelement4
void tagelement3(){
  attributes();
  tagelement4();
}



//tagelement4: '/' '>'
//  | '>' childswithend
void tagelement4(){

  if(peek()=='/'){
    match('/');
    match('>');
    push_cmd = 0;
    check_file = 0;
  }else{
    match('>');
    if (push_cmd || check_file) {
      myassert(0,"command/dependency should be self closing tags");
    }
    childswithend();
  }
}
