# 编译过程
## 预处理：处理所有的#开头的代码，包括头文件、宏定义、条件编译
    gcc -E hello.c -o hello.i
## 编译：语法检查以及将c语言变成汇编语言
    gcc -S hello.i -o hello.s
## 汇编：将汇编语言变成二进制
    gcc -c hello.s -o hello.o
## 链接：链接代码用到的其他文件(库文件等)
    gcc hello.o -o hello
# 常用参数
- -c
- -s
- -o
- -l dir 库名字
- -L dir 库路径
  
hello.c f1.c f2.c
# 静态库 
    - gcc -c  f1.c f2.c
    - ar -crv libname.a f1.o f2.o
    - gcc hello.c -o hello -static -L . -l name
# 动态库 
     - gcc -fPIC -shared -o libname.so f1.c f2.c
     - gcc hello.c -o hello -L . -l name
