
//#define DEBUG 

#include <sys/time.h>
#include <math.h>

#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 
  struct timeval start,end;
  gettimeofday(&start,NULL);
  
  fullnine fn;
  
  while(true){
    fn.runF();
    if(!fn.isok())
      continue;
    fn.runK();
    
 
    fn.showK();
    printf("\n\n");

    fn.showF();
    break;
  }
  gettimeofday(&end,NULL);
  int tt=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
  printf("耗时: %d\n",tt);
  return 0;
}

