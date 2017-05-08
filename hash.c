#include <stdlib.h>
#include <string.h>
#include "hash.h"



node_t * new_node()
{
  return (node_t *) malloc(sizeof(node_t));
}

hash_t new_hash()
{
  hash_t h;
  int i;
  for(i=0;i<NUM_BUCKETS;++i)
    h.table[i] = (node_t*) 0;
  return h;
}

node_t * hash_search( hash_t * s , char* k )
{

  int b = hashpjw(k);

  node_t * n = s->table[b];

  while(n != 0)
  {
		if(!strcmp(n->key , k))
			return n;
		n = n->right;
	}

	return 0;

}

node_t * hash_insert(hash_t * h, char* k, char c)
{

	if(hash_search(h,k) != 0)
	{
		hash_error = HASH_ID_ALREADY_EXISTS;
		return 0;
	}
	
	int b = hashpjw(k);
	node_t * n = insert_node(h->table + b , k , c);

	hash_error = HASH_SUCCESS;
	return n;

}



node_t * insert_node(node_t** lref,char* k,char c)
{

	node_t * n = new_node();
	n->right = *lref;
	*lref = n;

	(**lref).key = strdup(k);
	(**lref).chr = c;
	return *lref;

}


