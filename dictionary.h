#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#define KEY_LENGTH 1000
#define MAX_HASH_SLOT 10000


typedef struct _DNODE {
  struct _DNODE  *next;
  struct _DNODE  *prev;
  void    *data;        //  actual data points to URLNOD
  char key[KEY_LENGTH]; //  actual (URL) key 
  int count;//the count of the document
} __DNODE;

typedef struct _DNODE DNODE;

typedef struct _DICTIONARY {
  DNODE *hash[MAX_HASH_SLOT]; // the hash table of slots, each slot points to a DNODE
  DNODE *start;               // start of double link list of DNODES terminated by NULL pointer
  DNODE *end;                 // points to the last DNODE on this list
} __DICTIONARY;


typedef struct _DICTIONARY DICTIONARY;

extern DICTIONARY *dict;



DNODE* insertList(DICTIONARY* dict, DNODE* node_to_in, DNODE* location);
DNODE* createDictNode(char* key,void* data);
DNODE* insertWordNode(char* key,int hash_val,DNODE* findnode);


#endif
