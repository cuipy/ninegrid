
//#define DEBUG 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  每个格子的属性  
struct grid{
  int row_v;
  int col_v;
  int grid_v;
  int numb_v;
};

grid grids[81];

void initGrids();
// 向九宫格中循环放入0-8的数字
void putNumb();
// 验证数字在某一行，应该放入第几列，返回-1表示没有合适的位置 
int chkCol(int numb,int row);
// 验证某个格子是否允许放入某值
bool chkNumb(int numb,int index);
// 从九宫格中清除某个数字，当没空格放入数字的时候调用
void cleanNumb(int numb);
// 显示为九宫格
void show();

int main(){ 
  srand((unsigned int)time(NULL));

  initGrids();
  putNumb();

  show();
#ifdef DEBUG 
  for (int i=0;i<81;i++){
    printf("row:%d col:%d grid:%d numb:%d \n"
    ,grids[i].row_v  ,grids[i].col_v,grids[i].grid_v,grids[i].numb_v);
  }
#endif

  return 0;
}

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
      i=(tnumb-1)*9;
            
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
    printf("  %d",grids[i].numb_v);
    if(i%9==8){
      printf("\n");
    } 
  }

}
