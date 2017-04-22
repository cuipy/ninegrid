

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
