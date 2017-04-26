
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
    int idx=randIndexNoZero();
	int tmpNumb=grids[idx].numb_v;
	if(tmpNumb==0){
      continue;
    }
    grids[idx].numb_k=0;
	
	// 检查该单元格是否一定只能是某值
    if(chkIndexIsNumb(idx,tmpNumb)){
      continue;
    }
    grids[idx].numb_k=tmpNumb;
  }
}

// 随机得到某个非空单元格
int fullnine::randIndexNoZero(){
  int idx=rand()%81;
  while(grids[idx%81].numb_k==0){
    idx++;
  }
  return idx%81;
}


// 检查某行区一定不包含某数字
bool fullnine::chkRowAreaNoNumb(int row_area,int numb){

  
}
// 检查某行区一定包含某数字
bool fullnine::chkRowAreaIncNumb(int row_area,int numb){
  
}

// 检查某列区一定不包含某数字
bool fullnine::chkColAreaNoNumb(int col_area,int numb){
  
}
// 检查某列区一定包含某数字
bool fullnine::chkColAreaIncNumb(int col_area,int numb){
  
}

// 检查某索引是否可以填入某值,但不是绝对确定
bool fullnine::chkIndexCanNumb(int grid_index,int numb){
  // 比较的和过滤的单元格不能相同，如果已经有值，则肯定不允许
  if(numb==0){
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
    if(grids[rindex].numb_k==0&&chkIndexIsNumb(rindex,numb)){
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
    if(grids[cindex].numb_k==0&&chkIndexIsNumb(cindex,numb)){
      return false;
    }

  }
  return true;
}

// 验证某单元格的值一定是numb
bool fullnine::chkIndexIsNumb(int grid_index,int numb){
  if(numb==0){
    return false;
  }
  // 非空情况
  if(grids[grid_index].numb_k!=0){
    return grids[grid_index].numb_k==numb;
  }
  
  // 空单元格的情况
  if(getIndexNumb(grid_index,0)>0){
    return true;
  }
  //if(chk2KIndexIsNumb(grid_index,numb)){
  //  return true;
  //}
  
  return false;
}

// 以第一种方法验证某单元格的值
int fullnine::getIndexNumb(int grid_index,int deep){
  if(grids[grid_index].numb_k>0){
    return grids[grid_index].numb_k;
  }
  
  int trow=grid_index/9;
  int tcol=grid_index%9;
  int n2=0;

  for(int i=0;i<9;i++){
    int row_index=trow*9+i;
    if(row_index!=grid_index){
    if(grids[row_index].numb_k!=0){
      n2|=1<<(grids[row_index].numb_k-1);
    }else if(deep<MAX_DEEP){
      
      int rn=getIndexNumb(row_index,deep+1);
      if(rn-->0){
        n2|=1<<rn;
      }
    }}

    int col_index=i*9+tcol;
    if(col_index!=grid_index){
    if(grids[col_index].numb_k!=0){
      n2|=1<<(grids[col_index].numb_k-1);
    }else if(deep<MAX_DEEP){
      int cn=getIndexNumb(col_index,deep+1);
      if(cn-->0){
        n2|=1<<cn;
      }
    }}

    int g_index=(trow/3*3*9+tcol/3*3)+i/3*9+i%3;
    if(g_index!=grid_index){
    if(grids[g_index].numb_k!=0){
      n2|=1<<(grids[g_index].numb_k-1);
    }else if(deep<MAX_DEEP){
      int gn=getIndexNumb(g_index,deep+1);
      if(gn-->0){
        n2|=1<<gn;
      }
    }}
  }
  switch(n2){
  case 510:
    return 1;
  case 509:
    return 2;
  case 507:
    return 3;
  case 503:
    return 4;
  case 495:
    return 5;
  case 479:
    return 6;
  case 447:
    return 7;
  case 383:
    return 8;
  case 255:
    return 9;
  default:
    return -1;
  }
}
// 以第二种方式验证某空单元格一定是numb
// 采用宫内除余法
bool fullnine::chk2KIndexIsNumb(int grid_index,int numb){
  // 验证同row的另外两个单元格不是numb，并验证同宫的其他两个区不存在numb
  // 单元格所在行区
  int cRowArea=grids[grid_index].row_area;
  
  bool rstate=true;
  for(int i=cRowArea*3;i<cRowArea*3+3;i++){
    if(i==grid_index){
      continue;
    }
    if(grids[i].numb_k==numb){
      return false;
    }
    if(!chkIndexNotNumb(i,numb,0)){
      rstate=false;
    } 
  }
  
  // 两个行区数组
  int tRowAreas[2];
  sameGridRowArea(grid_index,tRowAreas);
  
  for(int i=0;i<2;i++){
    if(!chkRowAreaNoNumb(tRowAreas[i],numb)){
      rstate=false;
    }
  }
  if(!rstate){
    return false;
  }


  return true;
}

bool fullnine::chkIndexIsNumb(int grid_index,int numb,int deep){
  if(deep>MAX_DEEP){
    return false;
  }
  return chkIndexIsNumb(grid_index,numb,deep++);
}

// 检查某单元格的值一定不是numb
bool fullnine::chkIndexNotNumb(int grid_index,int numb){
  if(grids[grid_index].numb_k!=0){
    return grids[grid_index].numb_k!=numb;
  }
  int rcgs[20];
  sameRowColGrid(grid_index,rcgs);

  for(int i=0;i<20;i++){
    if(chkIndexIsNumb(rcgs[i],numb,0)){
      return true;
    }
  }
  return false;
}
bool fullnine::chkIndexNotNumb(int grid_index,int numb,int deep){
  if(deep>MAX_DEEP){
    return false;
  }

  return chkIndexNotNumb(grid_index,numb,deep++);
}

// 获得某一个单元格同行、同列、同宫的索引列表
void fullnine::sameRowColGrid(int grid_index,int *rcgs){
  int j=0;
  for(int i=0;i<81;i++){
    if(i==grid_index){
      continue;
    }
    if(grids[i].row_v==grids[grid_index].row_v
      ||grids[i].col_v==grids[grid_index].col_v
      ||grids[i].grid_v==grids[grid_index].grid_v){
      rcgs[j++]=i;
    }

  }  
}

// 获取同行区的其他两个单元格
void fullnine::sameRowArea(int grid_index,int *gs){
  int j=0;
  for(int i=0;i<81;i++){
    if(i==grid_index){
      continue;
    }
    if(grids[i].row_area==grids[grid_index].row_area){
      gs[j++]=i;
    }
  }
}

void fullnine::sameColArea(int grid_index,int *gs){
  int j=0;
  for(int i=0;i<81;i++){
    if(i==grid_index){
      continue;
    }
    if(grids[i].col_area==grids[grid_index].col_area){
      gs[j++]=i;
    }
  }

}

void fullnine::sameGridRowArea(int grid_index,int *ras){
  int j=0;
  int grid=grids[grid_index].grid_v;
  for(int i=0;i<3;i++){
    int ngrid=grid*3+i;
    if(ngrid==grid){
      continue;
    }
    ras[j++]=ngrid;
  }
}
void fullnine::sameGridColArea(int grid_index,int *cas){
  int j=0;
  int colArea=grids[grid_index].col_area/3*3;
  for(int i=colArea;i<colArea+3;i++){
    if(i==grids[grid_index].col_area){
      continue;
    }
    cas[j++]=i;
  }
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

