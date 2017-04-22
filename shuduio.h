
#ifndef __shuduio_h__
#define __shuduio_h__

class shuduio{
public:
  // 读取某行的的内容
  static char* readline(char *filepath,int line);
  static char* readl1(char *filepath);
  // append str 在文件结尾
  static int append(char *filepath,char *str);
  
  static void mkdir(char *path);
  
};
#endif  // __shuduio_h__
