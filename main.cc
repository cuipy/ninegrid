
//#define DEBUG 

#include "grid.h"
#include "fullnine.h"

int main(){ 

  fullnine fn;
  fn.run();

  fn.show();
#ifdef DEBUG 
  for (int i=0;i<81;i++){
    printf("row:%d col:%d grid:%d numb:%d \n"
    ,grids[i].row_v  ,grids[i].col_v,grids[i].grid_v,grids[i].numb_v);
  }
#endif

  return 0;
}

