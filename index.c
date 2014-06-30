#include "hash.h"
#include "index.h"
#include "dictionary.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int max(int a,int b){
  if(a>b)
    return a;
  return b;
}

int loadIndex(const char *filename){
  FILE *fp;

  int max_file_id=0;

  if((fp=fopen(filename, "r")) == NULL) {
       printf("%s\n", "open file error");
    } else {

        for(;;) {
            char word[100];
            int count;

            if(feof(fp))
              break;

            if(fscanf(fp, "%s",word)!=1)
              break;
            fscanf(fp, "%d ",&count);
              
            //printf("%s\n", word);

            

            for(int i=0;i<count;i++){
              int file_id=0;
              
              int each_count;
              fscanf(fp, "%d",&file_id);
              fscanf(fp, "%d",&each_count);

              max_file_id=max(max_file_id,file_id);

              for(int j=0;j<each_count;j++)
                  insertDict(word,file_id);
            }
            
        }

      fclose(fp);
    }

    return max_file_id;
}

int saveIndexToFile(const char *filename){
  FILE *fp;

  if((fp=fopen(filename, "w")) == NULL) {
       printf("%s\n", "open file error");
    } else {

      for(DNODE* node=dict->start;node!=0;node=node->next){
        char word[100];
        strcpy(word,node->key);
        fprintf(fp,"%s %d ", word, node->count);
        DOCNODE* doc=(DOCNODE*)(node->data);
        while(doc){
          fprintf(fp,"%d %d ", doc->doc_id, doc->freq);
          doc=doc->next;
        }

        fprintf(fp,"\n");
      }

      fclose(fp);
    }

    return 0;
}

DOCNODE* createDocNode(int pagenum){
//Create new node
  DOCNODE* node=(DOCNODE*)malloc(sizeof(DOCNODE));
  node->doc_id=pagenum;
  node->freq=1;
  node->next=0;

  return node;
}

//insert, or increase count
int insertDocNode(DNODE* findnode,int pagenum){
  if(findnode->data==0)
  {
      DOCNODE* new_doc_node=createDocNode(pagenum);
      findnode->data=(void*)new_doc_node;
      (findnode->count)++;
      return 0;
  }

  DOCNODE* rv=(DOCNODE* )findnode->data;
  while(1){
    if(rv->doc_id==pagenum){
      rv->freq++;
      return 0;
    }

    if(rv->next)  
      rv=rv->next;
    else 
      break;
  }

  rv->next=createDocNode(pagenum);
  (findnode->count)++;
  return 0;

}

DNODE* findNode(char* word){
  int hash_val=hash1(word)%MAX_HASH_SLOT;
  DNODE* findnode=dict->hash[hash_val];
  
  while(findnode){
      //find the node
      if(strcmp(findnode->key,word)==0)
        return findnode;
      findnode=findnode->next;
  }

  return 0;
}

int insertDict(char* word, int pagenum){

  int hash_val=hash1(word)%MAX_HASH_SLOT;
  DNODE* findnode=dict->hash[hash_val];
  
  while(findnode){
      if((hash1(findnode->key)%MAX_HASH_SLOT)!=hash_val)
        break;
      //find the node
      if(strcmp(findnode->key,word)==0)
        return insertDocNode(findnode,pagenum);
      findnode=findnode->next;
  }
  //The word not currently in the Dict
  DNODE* rv=insertWordNode(word,hash_val,findnode);
  return insertDocNode(rv,pagenum);
}
