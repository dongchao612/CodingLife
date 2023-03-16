# main.c

# 最终目标
main:main.o   # 目标文件:依赖文件 链接
	gcc main.o -o main

main.o:main.S # 目标文件:依赖文件 汇编
	gcc -c main.S -o main.o

main.S:main.i # 目标文件:依赖文件 编译
	gcc -S main.i -o main.S

main.i:main.c # 目标文件:依赖文件 预处理
	gcc -E main.c -o main.i
	
.PHONY:
clear:
	rm main.i main.S  main.o  -rf
clearall:
	rm main.i main.S  main.o main -rf
