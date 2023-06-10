main:main.o 	# 目标文件:依赖文件
	gcc main.o -o mainStatic -L . -l SeqListStatic

main.o:main.c 				# 目标文件:依赖文件
	gcc main.c -c -o main.o

.PHONY:
clear:
	rm main.o   -rf
clearall:
	rm main.o  main -rf
