
#ifndef __shuduio_h__
#define __shuduio_h__

class shuduio{
public:
  // 读取某行的的内容
  static char* readLine(char *filepath,int line);
  static char* readL1(char *filepath);
  // append str 在文件结尾
  static int appendLine(char *filepath,char *str);
  
  static void mkdir(char *path);
  
};
#endif  // __shuduio_h__
