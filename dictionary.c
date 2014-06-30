#include "dictionary.h"
#include <string.h>
#include <stdlib.h>

DNODE* insertList(DICTIONARY* dict, DNODE* node_to_in, DNODE* location){
  //The first node
  if(dict->start==0 && dict->end==0){
      node_to_in->prev=NULL;
      node_to_in->next=NULL;
      dict->start=node_to_in;
      dict->end=node_to_in;
      return node_to_in;
  }

  if(dict->end==location){
      node_to_in->prev=dict->end;
      node_to_in->next=NULL;

      dict->end->next=node_to_in;

      dict->end=dict->end->next;

      return node_to_in;
  }

  DNODE* original_next=location->next;
  node_to_in->prev=location;
  node_to_in->next=original_next;

  location->next=node_to_in;
  original_next->prev=node_to_in;

  return node_to_in;
}


DNODE* createDictNode(char* key,void* data){
  DNODE* node_d=(DNODE*)malloc(sizeof(DNODE));
  node_d->data=data;
  strcpy(node_d->key,key);
  node_d->count=0;
  return node_d;
}

DNODE* insertWordNode(char* key,int hash_val,DNODE* findnode){
  DNODE* new_node=createDictNode(key,0);
  if(dict->hash[hash_val]==0){
      dict->hash[hash_val]=new_node;
      return insertList(dict, new_node, dict->end);
  }

  //just scan the last node of the double like list to NULL
  if(dict->hash[hash_val]!=0 && findnode==0)
    return insertList(dict, new_node, dict->hash[hash_val]); 
  
  return insertList(dict, new_node, findnode->prev); 
}
