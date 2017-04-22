

#include <stdio.h>
#include <stdlib.h>
#include "shuduio.h"

void savefile(char *filePath,char *str){
  
  FILE *fds=fopen(filepath,"rw+");
  fwrite(str,sizeof(*str),1,fds);
  
  fclose(fds);
	
}

