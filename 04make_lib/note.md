# 编译过程


## 预处理：处理所有的#开头的代码，包括头文件、宏定义、条件编译
    gcc -E main.c -o main.i
## 编译：语法检查以及将c语言变成汇编语言
    gcc -S main.i -o main.s
## 汇编：将汇编语言变成二进制
    gcc -c main.s -o main.o
## 链接：链接代码用到的其他文件(库文件等)
    gcc main.o -o main
# 常用参数
```text
-l dir 库名字
-L dir 库路径
```
  
源文件：hello.c f1.c f2.c

# 静态库 
    - gcc -c  f1.c f2.c
    - ar -crv libstatic.a f1.o f2.o
    - gcc main.c -o main -static -L . -l static


# 动态库 
     - gcc -fPIC -shared -o libdynamic.so f1.c f2.c
     - gcc main.c -o main -L . -l dynamic


> 这种静态库，不需要头文件