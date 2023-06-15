# tool1.c tool1.h tool2.c tool2.h main.c 

main:main.o tool1.o tool2.o 	# 目标文件:依赖文件
	gcc main.o tool1.o tool2.o -o main

main.o:main.c	# 目标文件:依赖文件
	gcc main.c -c -o main.o

tool1.o:tool1.c	# 目标文件:依赖文件
	gcc tool1.c -c -o tool1.o
    
tool2.o:tool2.c	# 目标文件:依赖文件
	gcc tool2.c -c -o tool2.o


.PHONY:
clean:
	rm main.o tool1.o tool2.o -r
cleanall:
	rm main.o tool1.o tool2.o main -r
