
//#define DEBUG 

#include <sys/time.h>

#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 
  struct timeval start,end;
  gettimeofday(&start,NULL);
  
  fullnine fn;
 
  fn.runF();
  if(fn.isok()){
    fn.runK();
	fn.showK();
  }
  gettimeofday(&end,NULL);
  int tt=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
  printf("耗时: %d\n",tt);
  return 0;
}

