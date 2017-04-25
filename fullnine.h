
#ifndef __fullnine_h__
#define __fullnine_h__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

class fullnine{
private:	
  grid grids[81];
  bool _isok;
public:
  // structure  and destory 
  fullnine();
  ~fullnine();
  
  void loadF(char *numbs);
  // 执行生成填满的九宫
  void runF();
  // 置空处理
  void runK();
  // 显示为九宫格
  void showF();
  void showK();
  
  bool isok();
  
  void strF(char *str);
private:
  // 向九宫格中循环放入0-8的数字
  void putNumbF();
  // 验证数字在某一行，应该放入第几列，返回-1表示没有合适的位置 
  int chkColF(int numb,int row);
  // 验证某个格子是否允许放入某值
  bool chkNumbF(int numb,int index);
  // 从九宫格中清除某个数字，当没空格放入数字的时候调用
  void cleanNumbF(int numb);
  // 以第一种算法检查某个索引位置可否置空
  bool chk1IndexZeroK(int index);
  // 以第二种算法检查某索引的位置可否置空
  bool chk2IndexZeroK(int index);
  
  // 检查某单元格是否允许放入某值，判断的时候不能以filterIndex做比较
  bool chkIndexCanNumb(int grid_index,int filterIndex,int numb);
  //  检查某单元格一定是某值
  bool chkIndexIsNumb(int grid_index,int filterIndex,int numb);
  bool chk1KIndexIsNumb(int grid_index,int numb);
  bool chk2KIndexIsNumb(int grid_index,int numb);

  int randIndexNoZero();
  
  // 检查某行区一定不包含某数字
  bool chkRowAreaNoNumb(int row_area,int filterIndex,int numb);
  // 检查某行区一定包含某数字
  bool chkRowAreaIncNumb(int row_area,int filterIndex,int numb);
  // 检查某列区一定不包含某数字
  bool chkColAreaNoNumb(int col_area,int filterIndex,int numb);
  // 检查某列区一定包含某数字
  bool chkColAreaIncNumb(int col_area,int filterIndex,int numb);

};

#endif  // __fullnine_h__
