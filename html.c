#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "html.h"

int reWindStart(char* buf){
	int n_count=0,i=0;
	for(;buf[i]!=0;i++){
		if(2==n_count)
			break;
		if(buf[i]=='\n')
			n_count++;

	}
	return i;

}

int getNextWordFromHTMLDocument(char* loadedDocument, char* word, int position){
	int start=-1;
	for(;loadedDocument[position]!=0;position++){
		if(-1==start && !isWordPart(loadedDocument[position]))
			continue;
		else if(-1!=start && !isWordPart(loadedDocument[position]))
			break;
		else{
			if(-1==start)
				start=position;
		}

	}
	if(-1==start)
		return -1;
	strncpy(word, loadedDocument+start, position-start); 
	word[position-start]=0;
	NormalizeWord(word);
	return position;
  
}

int isWordPart(char c){
	if(c>='A' && c<='Z')
		return 1;
	if(c>='a' && c<='z')
		return 1;
	if(c>='0' && c<='9')
		return 1;

	return 0;
}



void removeWhiteSpace(char* html) {
  int i;
  char *buffer = malloc(strlen(html)+1), *p=malloc (sizeof(char)+1);
  memset(buffer,0,strlen(html)+1);
  for (i=0;html[i];i++) {
    if(html[i]>32){
      sprintf(p,"%c",html[i]);
      strcat(buffer,p);
    }
  }
  strcpy(html,buffer);
  free(buffer); free(p);
}

void NormalizeWord(char* word) {
  int i = 0;
  while (word[i]) {
      // NEW
    if (word[i] < 91 && word[i] > 64) // Bounded below so this funct. can run on all urls
      // /NEW
      word[i] += 32;
    i++;
  }
}
