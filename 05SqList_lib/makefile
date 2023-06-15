main:main.o   # 目标文件:依赖文件 链接
	gcc main.o -o mainStatic -static -L . -l SeqList
	gcc main.o -o mainDynamic  -L . -l SeqList

main.o:main.c
	gcc main.c  -c -o   main.o

.PHONY:
clean:
	rm main.o  -rf
cleanall:
	rm main.o mainStatic mainDynamic -rf