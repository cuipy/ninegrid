

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "shuduio.h"

int shuduio::readL1(char *filepath,char *str,int len){
  return readLine(filepath,0,str,len);
}
int shuduio::readLine(char *filepath,int line,char *str,int len){
  if(filepath==NULL||str==NULL){
    return NULL;
  }
  
  FILE* fds=fopen(filepath,"r");
  if(fds==NULL){
    return NULL;
  }
  
  fseek(fds,0,SEEK_SET);
  
  while(line-->=0){
    if(feof(fds)){
      memset(str,0,sizeof(str));
      len=0;    
      break;  
    }
    fgets(str,len,fds);
  }
  return strlen(str);
}


int shuduio::appendLine(char *filepath,char *str){
  if(filepath==NULL||str==NULL||strlen(str)==0){
    return -1;
  }
  
  FILE* fds=fopen(filepath,"aw+");
  if(fds==NULL){
    return -1;
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
  return len;
}


void shuduio::mkdir(char *path){
  
  if(0!=access(path,0)){
    ::mkdir(path,S_IRUSR|S_IWUSR);
  }
	
}



