#ifndef _INDEX_H_
#define _INDEX_H_

#include "dictionary.h"



typedef struct _DOCUMENT{
  int doc_id;
  int freq;
  struct _DOCUMENT* next;


} __DOCUMENT;

typedef struct _DOCUMENT DOCNODE;

int saveIndexToFile(const char *filename);

int loadIndex(const char *filename);

DOCNODE* createDocNode(int pagenum);
int insertDict(char* word, int pagenum);
int insertDocNode(DNODE* findnode,int pagenum);
DNODE* findNode(char* word);


#endif
