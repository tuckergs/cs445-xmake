
#include <string.h>
#include <stdlib.h>

#include "Str.h"



Str Str_init ( int st )
{

	Str v;

	v.size = 0;
	v.capacity = 0;
	v.str = strdup("");

	return v;

}


Str append ( Str l , char x )
{

	int i;

	if ( l.size + 1 > l.capacity )
	{

		//Reallocate :(

		char* nstr;

		l.capacity = (l.capacity << 1) + 1;

		nstr = (char*) malloc ( l.capacity + 1 ); 


    for ( i = 0 ; i < l.size ; ++i )
      nstr [ i ] = (l.str) [ i ];

    free ( l.str );


		l.str = nstr;

	}

	(l.str) [ l.size ] = x;
  (l.str) [l.size + 1] = 0;
	++l.size;

	return l;

}

