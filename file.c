#include "file.h"
#include <dirent.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getDocumentId(char* buf){
  /*int i;
  char url[200];
  sscanf(buf, "%s\n%d\n",url,&i);
  return i;*/
  int i=0;
  int rv=0;
  while(buf[i]>='0' && buf[i]<='9'){
    rv*=10;
    rv+=(int)(buf[i++]-'0');
  }

  return rv;

}

char* loadDocument(char* filename){
  FILE *f = fopen(filename, "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(fsize + 1);
  fread(string, fsize, 1, f);
  fclose(f);
  string[fsize] = 0;
  return string;
}

int scanFolder(char *names[], char *location,char *names_nopath[]){
  struct dirent **namelist;
  struct stat statbuf;
  int n,k=0;

  n = scandir(location, &namelist, 0, alphasort);
  if (n < 0)
    perror("scandir");
  else {
    while(n--) {
      char fullpath[100];
      sprintf(fullpath,"%s/%s",location,namelist[n]->d_name);
      
      if(stat(fullpath, &statbuf) == -1){
	       perror("stat");
	       return -1;
	     }

      if(S_ISREG(statbuf.st_mode) && strstr(namelist[n]->d_name,".html")){
	     names[k]=(char*)malloc(sizeof(fullpath));
       names_nopath[k]=(char*)malloc(sizeof(namelist[n]->d_name));

	     strcpy(names[k],fullpath);
       strcpy(names_nopath[k],namelist[n]->d_name);
       //printf("%s\n", names_nopath[k]);
	     k++;
      }
      

      free(namelist[n]);
    }
    free(namelist);
  }
  return k;

}
