main:main.o   # 目标文件:依赖文件 链接
	gcc main.o -o main -l sqlite3

main.o:main.c
	gcc main.c  -c -o   main.o

.PHONY:
clean:
	rm main.o  -rf
cleanall:
	rm main.o main -rf