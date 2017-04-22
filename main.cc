
//#define DEBUG 

#include <sys/stat.h>

#include "grid.h"
#include "fullnine.h"
#include "shuduio.h"

int main(){ 

  //fullnine fn;
  //fn.run();

  //fn.show();
  
  mkdir("save",S_IRUSR|S_IWUSR);
  savefile("save/file1.txt","HelloWorld\n");
  

  return 0;
}

