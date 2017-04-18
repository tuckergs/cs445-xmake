#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void match(int type){
  assert( peek(PRESERVE_TEXT) == type );
}

void document(){
  match('<');
  document2();
}

void document2(){
  match('?');
  match('x');
  match('m');
  match('l');
  attributes();
  match('?');
  match('>');
  root();
}
