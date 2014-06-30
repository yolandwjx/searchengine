#include "interpreter.h"
#include <stdlib.h>
#include "index.h"
#include <string.h>

void quick_sort(int* idx,int* val,int start,int end){
	if(start>=end)
		return;
	int i=start-1;
	int j=start;
	for(;j<=end-1;j++){
		if(val[j]>=val[end])
			swap(++i,j,idx,val);
	}
	swap(++i,j,idx,val);
	quick_sort(idx,val,start,i-1);
	quick_sort(idx,val,i+1,end);
	return;
}

void swap(int i,int j,int* idx,int *val){
	int temp;
	temp=idx[i];
	idx[i]=idx[j];
	idx[j]=temp;

	temp=val[i];
	val[i]=val[j];
	val[j]=temp;
}

void interpret(int argc, char const *argv[],int* record,int max_file_id)
{
	for(int i=2;i<argc;i++){
		char word[100];
		strcpy(word,argv[i]);
		if(2==i)
			mergeWord(word,record,max_file_id);
		else if(isOr(word) || isAnd(word))
			continue;
		else if(isOr(argv[i-1]))
			addWord(word,record);
		else
			mergeWord(word,record,max_file_id);
	}
}

int isOr(const char *input){
	if(strcmp(input,"OR")==0)
		return 1;
	return 0;
}

int isAnd(const char *input){
	if(strcmp(input,"AND")==0)
		return 1;
	return 0;
}

void addWord(char* word,int *record){
	DNODE* fn=findNode(word);
	DOCNODE* fd=(DOCNODE*)(fn->data);
	while(fd){
		record[fd->doc_id]+=fd->freq;
		fd=fd->next;
	}
	return;
}

void mergeWord(char* word,int* record,int max_file_id){
	int *record_new=(int *)malloc(sizeof(int)*(max_file_id+1));
	memset(record_new,0,max_file_id+1);

	DNODE* fn=findNode(word);
	DOCNODE* fd=(DOCNODE*)(fn->data);
	while(fd){
		record_new[fd->doc_id]+=fd->freq;
		fd=fd->next;
	}

	for(int i=1;i<=max_file_id;i++){
		if(record_new[i]>0)
			record[i]+=record_new[i];
		else
			record[i]=0;
	}

	free(record_new);

	return;
}


