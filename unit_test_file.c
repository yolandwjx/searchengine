#include "file.h"
#include "html.h"
#include "index.h"
#include "interpreter.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


DICTIONARY* dict = NULL; 

int main(int argc, char const *argv[])
{
	dict=(DICTIONARY*)malloc(sizeof(DICTIONARY));
  	//Init the dict
  	//point all the hash table entry to NULL
  	memset(dict->hash,0, MAX_HASH_SLOT);
  	dict->start=0;
  	dict->end=0;

  	char data_file[100];
  	sprintf(data_file,"%s/data.dat",argv[1]);

	int max_file_id=loadIndex(data_file);
	int *record=(int *)malloc(sizeof(int)*(max_file_id+1));
	memset(record,0,max_file_id+1);

	interpret(argc,argv,record,max_file_id);
	int result_size=0;
	for(int i=1;i<=max_file_id;i++){
		if(record[i]>0)
			result_size++;
	}

	int *idx_arr=(int *)malloc(sizeof(int)*(result_size));
	int *val_arr=(int *)malloc(sizeof(int)*(result_size));

	result_size=0;
	for(int i=1;i<=max_file_id;i++){
		if(record[i]>0){
			idx_arr[result_size]=i;
			val_arr[result_size++]=record[i];
		}
			
	}

	//for(int i=0;i<result_size;i++)
	//	printf("%d %d\n",idx_arr[i], val_arr[i]);

	quick_sort(idx_arr,val_arr,0,result_size-1);

	for(int i=0;i<result_size;i++){
		char URL[200];
		char html_file[200];
		sprintf(html_file,"%s/%d.html",argv[1],idx_arr[i]);
		FILE *fp;
  		if((fp=fopen(html_file, "r")) == NULL) {
       		printf("%s\n", "open file error");
    	} else {
    		fscanf(fp,"%s",URL);
    		fclose(fp);
    	}
		printf("Document ID:%d URL:%s\n",idx_arr[i], URL);
	}




	return 0;
}
