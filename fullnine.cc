
#include <string.h>

#include "grid.h"
#include "fullnine.h"


fullnine::fullnine(){
  
  for(int i=0;i<81;i++){
    grids[i].row_v=i/9;
    grids[i].col_v=i%9;
    grids[i].grid_v=i%9/3+i/9/3*3;
    grids[i].numb_v=0;
	grids[i].numb_k=0;
  } 
  srand((unsigned int)time(NULL));

}

fullnine::~fullnine(){
  
}

void fullnine::loadF(char *numbs){
  
  if(numbs==NULL||strlen(numbs)<81){
    return;  
  }
  
  for(int i=0;i<81;i++){
	if(numbs[i]<'1'||numbs[i]>'9'){
      _isok=false;
      return;
    }
	
	grids[i].numb_v=numbs[i]-'0';
	grids[i].numb_k=0;
  }

}

// 执行填充 完全解 的81个值
void fullnine::runF(){
  for(int i=0;i<81;i++){
    grids[i].numb_v=0;
  } 
  _isok=true; 
  putNumbF();
}

void fullnine::strF(char *str){
  for(int i=0;i<81;i++){
    str[i]=grids[i].numb_v+'0';
  }
}
bool fullnine::isok(){
  return _isok;
}
void fullnine::putNumbF(){
  int trycnt=200;
  for(int i=0;i<81;i++){
    if(trycnt--<=0){
      _isok=false;
      break;
    }
	
    int tnumb=i/9+1;
    int trow=i%9;
    int tcol=chkColF(tnumb,trow);
    // 没有任何符合的数据	
    if(tcol<0){
      if(tnumb>8){
        tnumb=8;
      }
      cleanNumbF(tnumb);
	  
      i=(tnumb-1)*9-1;
            
      continue;
    }
    
    grids[trow*9+tcol].numb_v=tnumb;
  }
}

// 检查某个值在某行比较合适放入的列
int fullnine::chkColF(int numb,int row){
  //随机生成一个列值
  int tcol=rand()%9;
  // 准备判断9次试试这一行到底哪个位置合适
  int cnt=9;
  while(true){
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
   if(!chkNumbF(numb,row*9+tcol)){
     tcol++;
     continue;
   }
   return tcol;    
 }
 
 return -1;
}
// 验证某格是否可以放入某numb
bool fullnine::chkNumbF(int numb,int index){
  if(grids[index].numb_v!=0){
    return false;
  }
  
  int trow=grids[index].row_v;
  int tcol=grids[index].col_v;

  for(int i=0;i<9;i++){
    int row_index=trow*9+i;
    if(row_index!=index&&grids[row_index].numb_v==numb){
      return false;
    }
	
    int col_index=i*9+tcol;
    if(col_index!=index&&grids[col_index].numb_v==numb){
      return false;
    }
    
    int grid_index=(trow/3*3*9+tcol/3*3)+i/3*9+i%3;
    if(grid_index!=index&&grids[grid_index].numb_v==numb){
      return false;
    }
    	
  }

  return true;
}

void fullnine::cleanNumbF(int numb){
  for(int i=0;i<81;i++){
    if(grids[i].numb_v>=numb){
      grids[i].numb_v=0;
    }
  }
}


void fullnine::showF(){
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
  
#ifdef DEBUG 
  for (int i=0;i<81;i++){
    printf("row:%d col:%d grid:%d numb:%d \n"
    ,grids[i].row_v  ,grids[i].col_v,grids[i].grid_v,grids[i].numb_v);
  }
#endif

}

// 执行置空操作，最后形成考卷
void fullnine::runK(){
  
  for(int i=0;i<81;i++){
    grids[i].numb_k=grids[i].numb_v;
  }

  for(int i=0;i<3*81;i++){
    int idx=rand()%81;
    if(chkIndexK(idx)){
      grids[idx].numb_k=0;
    }
  }
}
// 判断某个位置可否为空
bool fullnine::chkIndexK(int index){
  if(grids[index].numb_k==0){
    return false; 
  }
  int n=511;
  int n2=0;
  
  int trow=grids[index].row_v;
  int tcol=grids[index].col_v;

  for(int i=0;i<9;i++){
    int row_index=trow*9+i;
    if(grids[row_index].numb_k!=0)
      n2|=1<<(grids[row_index].numb_k-1);
    
    int col_index=i*9+tcol;
    if(grids[col_index].numb_k!=0)
      n2|=1<<(grids[col_index].numb_k-1);

    int grid_index=(trow/3*3*9+tcol/3*3)+i/3*9+i%3;
    if(grids[grid_index].numb_k!=0)
      n2|=1<<(grids[grid_index].numb_k-1);
    if(n2==n){
      return true;
    }
  }
  return false;
}

void fullnine::showK(){
  for(int i=0;i<81;i++){
    if(grids[i].grid_v%2==0){
      if(grids[i].numb_k==0){
        printf("  \033[40;32m_\033[0m");
      }else{ 
        printf("  \033[40;32m%d\033[0m",grids[i].numb_k);
      }
    }else{
      if(grids[i].numb_k==0){
        printf("  \033[40;37m_\033[0m");
      }else{
        printf("  \033[40;37m%d\033[0m",grids[i].numb_k);
      }
    }

    if(i%9==8){
      printf("\n");
    } 
  }

}

