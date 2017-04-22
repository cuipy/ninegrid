
//#define DEBUG 



#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 

  //fullnine fn;
  //fn.run();

  //fn.show();
  
  char *str=new char[100];
  int len=shuduio::readL1("file1",str,100);
  printf("%d  %s",len,str);
  
  return 0;
}

