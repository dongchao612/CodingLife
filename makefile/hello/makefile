# hello.c

# 最终目标
hello:hello.o   # 目标文件:依赖文件 链接
	gcc hello.o -o hello

hello.o:hello.S # 目标文件:依赖文件 汇编
	gcc -c hello.S -o hello.o

hello.S:hello.i # 目标文件:依赖文件 编译
	gcc -S hello.i -o hello.S

hello.i:hello.c # 目标文件:依赖文件 预处理
	gcc -E hello.c -o hello.i
	
.PHONY:
clear:
	rm hello.i hello.S  hello.o  -rf
clearall:
	rm hello.i hello.S  hello.o hello -rf