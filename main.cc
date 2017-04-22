
//#define DEBUG 



#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 
 
  fullnine fn;
  int i=100000;
  while(i-->0){
  fn.run();
  if(fn.isok()){
    char *str=new char[100];
    fn.tostring(str);
   // shuduio::appendLine("file1",str);
    printf("%s\n",str);
    free(str);
  }
  }
  return 0;
}

