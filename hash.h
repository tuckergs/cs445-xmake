
#ifndef HASH_H_
#define HASH_H_

#define NUM_NODES 15

struct hash_s;
struct node_s;




#define NUM_BUCKETS 211

struct hash_s{
	struct node_s * table[ NUM_BUCKETS ];
};

struct node_s{
	struct node_s * right;
  char* key;
  char chr;
};


typedef struct hash_s hash_t;
typedef struct node_s node_t;

node_t * new_node();
hash_t new_hash();
node_t * insert_node(node_t**,char*,char);
node_t * hash_insert(hash_t*,char*,char);
node_t * hash_search(hash_t*,char*);


int hash_error;

#define HASH_ID_ALREADY_EXISTS -1
#define HASH_SUCCESS 0 


int hashpjw(char*);


#endif //HASH_H_
