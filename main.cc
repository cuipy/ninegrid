
//#define DEBUG 

#include <sys/time.h>

#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 
  struct timeval start,end;
  gettimeofday(&start,NULL);
  
  fullnine fn;
  int i=1000000;
  while(i-->0){
    fn.runF();
    if(fn.isok()){
      char *str=new char[100];
      fn.strF(str);
      shuduio::appendLine("file1",str);
      //printf("%s\n",str);
      free(str);
  }
  }
  gettimeofday(&end,NULL);
  int tt=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
  printf("耗时: %d\n",tt);
  return 0;
}

