

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "shuduio.h"

void shuduio::appendLine(char *filepath,char *str){
  if(filepath==NULL||str==NULL||strlen(str)==0){
    return;
  }
  
  FILE* fds=fopen(filepath,"aw+");
  if(fds==null){
    return;
  }
  
  int len=strlen(str);
  if(str[len-1]!='\n'){
    len++;
  }
  char *buf=new char[len+1];
  strcpy(buf,str);
  buf[len-1]='\n';
  buf[len]=0;
  
  fwrite(buf,len,1,fds);
  fclose(fds);
  delete []buf;
}


void shuduio::mkdir(char *path){
  
  if(0!=access(path,0)){
    ::mkdir(path,S_IRUSR|S_IWUSR);
  }
	
}



