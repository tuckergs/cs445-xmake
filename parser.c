#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "lexer.h"
#include "parser.h"
#include <string.h>

//peek(): check next token without match it




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
    myassert(!strcmp(getcurtext,"xml"),"Expected \"xml\"");
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
  if(peek()=='<'){
    match('<');
    childswithend2();
  }else{
    //match(TEXTSTR);
    childswithend();
  }
}



//childswithend2: ID tagelement3 childswithend
//  | endtag2
void childswithend2(){
  if(peek()==ID){
    match(ID);
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
  }else{
    match('>');
    childswithend();
  }
}
