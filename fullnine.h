
#ifndef __fullnine_h__
#define __fullnine_h__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct fullnine{
	
	grid grids[81];
	
	// structure  and destory 
	fullnine();
	~fullnine();

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


};

#endif  // __fullnine_h__
