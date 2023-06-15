# gcc编译c源程序的过程

## 预处理
宏定义展开、头文件展开、条件编译等，同时将代码中的注释删除，这里并不会检查语法
```bash
gcc -E main.c -o main.i
```
##  编译
检查语法，将预处理后文件编译生成汇编文件
```bash
gcc -S main.i -o main.s
```
## 汇编
将汇编文件生成目标文件(二进制文件)
```bash
gcc -c main.s -o main.o
```
## 链接
C语言写的程序是需要依赖各种库的，所以编译之后还需要把库链接到最终的可执行程序中去
```bash
gcc main.o -o main
```