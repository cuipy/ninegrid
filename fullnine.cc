

#include "fullnine.h"

void initGrids(){
  for(int i=0;i<81;i++){
    grids[i].row_v=i/9;
    grids[i].col_v=i%9;
    grids[i].grid_v=i%9/3+i/9/3*3;
    grids[i].numb_v=0;
  } 
}

void putNumb(){
  int trycnt=10000;
  for(int i=0;i<81;i++){
    if(trycnt--<=0){
      break;
    }
	
    int tnumb=i/9+1;
    int trow=i%9;
    int tcol=chkCol(tnumb,trow);
    // 没有任何符合的数据	
    if(tcol<0){
      cleanNumb(tnumb);
      if(tnumb>7){
        tnumb=7;
      }
      i=(tnumb-1)*9-1;
            
      continue;
    }
    
    grids[trow*9+tcol].numb_v=tnumb;
  }
}

// 检查某个值在某行比较合适放入的列
int chkCol(int numb,int row){
  //随机生成一个列值
  int tcol=rand()%9;
  // 初始化列值ok的状态标记
  bool isok=false;
  // 准备判断9次试试这一行到底哪个位置合适
  int cnt=9;
  while(!isok){
   if(cnt--<=0){
     break;
   }
   tcol%=9;
   // 如果该列已经放入数字了
   if(grids[row*9+tcol].numb_v!=0){
     tcol++;
     continue;
   }
   // 如果该列不太合适放入numb,即行列宫中已经存在numb了
   if(!chkNumb(numb,row*9+tcol)){
     tcol++;
     continue;
   }
   return tcol;    
 }
 
 return -1;
}
// 验证某格是否可以放入某numb
bool chkNumb(int numb,int index){
  if(grids[index].numb_v!=0){
    return false;
  }
  int trow=index/9;
  int tcol=index%9;

  for(int i=0;i<81;i++){
    if(grids[i].row_v==grids[index].row_v
      ||grids[i].col_v==grids[index].col_v
      ||grids[i].grid_v==grids[index].grid_v){
      if(grids[i].numb_v==numb){
        return false;
      }
    }
  }
  return true;
}

void cleanNumb(int numb){
  if(numb>7){
	  numb=7;
  }
  for(int i=0;i<81;i++){
    if(grids[i].numb_v>=numb){
      grids[i].numb_v=0;
    }
  }
}


void show(){
  for(int i=0;i<81;i++){
    if(grids[i].grid_v%2==0){
      printf("  \033[40;32m%d\033[0m",grids[i].numb_v);
    }else{
      printf("  \033[40;37m%d\033[0m",grids[i].numb_v);
    }    


    if(i%9==8){
      printf("\n");
    } 
  }

}