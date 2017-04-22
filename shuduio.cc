

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

#include "shuduio.h"

void shudoio::mkdir(char *path){
  
  if(!access(path,0)){
    mkdir(path,S_IRUSR|S_IWUSR);
  }
	
}

