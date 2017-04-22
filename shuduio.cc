

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "shuduio.h"

void shuduio::mkdir(char *path){
  
  if(0!=access(path,0)){
    ::mkdir(path,S_IRUSR|S_IWUSR);
  }
	
}

