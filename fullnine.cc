
#include <string.h>

#include "grid.h"
#include "fullnine.h"


fullnine::fullnine(){
  
  for(int i=0;i<81;i++){
    grids[i].row_v=i/9;
    grids[i].col_v=i%9;
    grids[i].grid_v=i%9/3+i/9/3*3;
	grids[i].row_area=grids[i].row_v*3+grids[i].col_v/3;
	grids[i].col_area=grids[i].col_v+grids[i].row_v/3;
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
    int idx=randIndexK();
	
    if(chk1IndexZeroK(idx)){
      grids[idx].numb_k=0;
	  continue;
    }
    if(chk2IndexZeroK(idx)){
      grids[idx].numb_k=0;
	  continue;
    }
	
  }
}

int fullnine::randIndexK(){
  int idx=rand()%81;
  while(grids[idx%81].numb_k==0){
    idx++;
  }
  return idx%81;
}

// 判断某个位置可否为空,即该位置的值可唯一确定
// 本方法按照宫内唯余法
bool fullnine::chk1IndexZeroK(int index){
  if(grids[index].numb_k==0){
    return false; 
  }
  
  int trow=grids[index].row_v;
  int tcol=grids[index].col_v;
  
  // 检验当前宫的其他格，是否允许填入该值，如果都不允许，则一定当前格的值是唯一确定的
  for(int i=0;i<9;i++){
    // 宫内每格的索引
    int grid_index=(trow/3*3*9+tcol/3*3)+i/3*9+i%3; 
    if(grid_index==index){
      continue;
    }

    if(chkIndexCanNumb(grid_index,index,grids[index].numb_k)){
      return false;
    }
	
  }
  
  return true;
}

// 判断某个位置可否为空
bool fullnine::chk2IndexZeroK(int index){
  if(grids[index].numb_k==0){
    return false; 
  }
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
    if(n2==511){
      return true;
    }
  }
  return false;
}
// 检查某行区一定不包含某数字
bool fullnine::chkRowAreaNoNumb(int row_area,int filterIndex,int numb){
  // 所在区域第一个格子的行和列
  int g1row=row_area/3;
  int g1col=row_area%3;
  int g1index=g1row*9+g1col;
  // 三个格子都不为空，且都不等于numb，则返回numb
  if(grids[g1index].numb_k!=0&&grids[g1index].numb_k!=numb&&grids[g1index+1].numb_k!=0&&grids[g1index+1].numb_k!=numb&&grids[g1index+2].numb_k!=0&&grids[g1index+2].numb_k!=numb){
    return true;
  }
  for(int i=0;i<9;i++){
    if(i%3==g1col){
      continue;
    }
    // 验证如果行上有一个其他单元格一定是numb，则返回true
    if(chkIndexIsNumb(g1row*9+i,filterIndex,numb)){
      return true;
    }
  } 
  
}
// 检查某行区一定包含某数字
bool fullnine::chkRowAreaIncNumb(int row_area,int filterIndex,int numb){
  
}

// 检查某列区一定不包含某数字
bool fullnine::chkColAreaNoNumb(int col_area,int filterIndex,int numb){
  
}
// 检查某列区一定包含某数字
bool fullnine::chkColAreaIncNumb(int col_area,int filterIndex,int numb){
  
}

// 检查某索引是否可以填入某值
bool fullnine::chkIndexCanNumb(int grid_index,int filterIndex,int numb){
  // 比较的和过滤的单元格不能相同，如果已经有值，则肯定不允许
  if(grid_index==filterIndex||numb==0){
    return false;
  }
  if(grids[grid_index].numb_k==numb){
    return true;
  }

  // 检查行是否允许填写该值
  for(int ri=0;ri<9;ri++){
    int rindex=grid_index/9*9+ri;
    // 如果是同一宫的，则跳过验证
    if(grids[rindex].grid_v==grids[grid_index].grid_v){
      continue;
    }
    if(grids[rindex].numb_k==numb){
      return false;
    }
    if(grids[rindex].numb_k==0&&chkKIndexIsNumb(rindex,filterIndex,numb)){
      return false;
    }
  }
  // 检查列是否允许填写该值
  for(int ci=0;ci<9;ci++){
    int cindex=ci*9+grid_index%9;
    if(grids[cindex].grid_v==grids[grid_index].grid_v){
      continue;
    }
    if(grids[cindex].numb_k==numb){
      return false;
    }
    if(grids[cindex].numb_k==0&&chkKIndexIsNumb(cindex,filterIndex,numb)){
      return false;
    }

  }
  return true;
}

// 验证某空单元格的值一定是numb
bool fullnine::chkIndexIsNumb(int grid_index,int filterIndex,int numb){
  if(grid_index==filterIndex||numb==0){
    return false;
  }
  if(grids[grid_index].numb_k!=0){
    return grids[grid_index].numb_k==numb;
  }
  
  
   
}

// 以第一种方法验证某空单元格一定是某个值
bool fullnine::chk1KIndexIsNumb(int grid_index,int filterIndex,int numb){
  
  int trow=grid_index/9;
  int tcol=grid_index%9;
  int n2=0;

  for(int i=0;i<9;i++){
    int row_index=trow*9+i;
    if(row_index!=grid_index&&grids[row_index].numb_k!=0)
      n2|=1<<(grids[row_index].numb_k-1);

    int col_index=i*9+tcol;
    if(col_index!=grid_index&&grids[col_index].numb_k!=0)
      n2|=1<<(grids[col_index].numb_k-1);

    int g_index=(trow/3*3*9+tcol/3*3)+i/3*9+i%3;
    if(g_index!=grid_index&&grids[grid_index].numb_k!=0)
      n2|=1<<(grids[grid_index].numb_k-1);
  }
  
  if(n2&(1<<(numb-1)==1<<(numb-1)){
    return false;
  }

  if(n2<511&&(n2|(1<<(numb-1)))==511){
    return true;
  }
  return false;
}
// 以第二种方式验证某空单元格一定是numb
// 采用宫内除余法
bool fullnine chk2KIndexIsNumb(int grid_index,int filterIndex,int numb){
  
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

