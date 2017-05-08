
#ifndef STR_H_
#define STR_H_




struct Str   // Vector struct
{

  char* str;
	int size;
	int capacity;

};


typedef struct Str Str;


Str append ( Str v , char x );

Str Str_init();
Str Str_clear(Str);


#endif //STR_H_

