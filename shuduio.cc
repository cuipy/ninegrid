

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shuduio.h"

void savefile(char *filepath,char *str){
  
  FILE *fds=fopen(filepath,"aw+");
  fwrite(str,strlen(str),1,fds);
  
  fclose(fds);
	
}

