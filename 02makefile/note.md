# 第一层 
```text
显示目标
目标文件:依赖文件
    指令
第一个目标文件是最终目标
```
```makefile
# tool1.c tool1.h tool2.c tool2.h main.c 

# 最终目标
test:main.o tool1.o tool2.o	# 目标文件:依赖文件
	gcc main.o tool1.o tool2.o -o test

main.o:main.c 				# 目标文件:依赖文件
	gcc main.c -c -o main.o

tool1.o:tool1.c 			# 目标文件:依赖文件
	gcc tool1.c -c -o tool1.o

tool2.o:tool2.c 			# 目标文件:依赖文件
	gcc tool2.c -c -o tool2.o

.PHONY:
clean:
	rm main.o tool1.o tool2.o  -rf
cleanall:
	rm main.o tool1.o tool2.o test -rf
```

# 第二层:
```
变量 = 替换 += 追加 := 恒等于
```
``` makefile
# tool1.c tool1.h tool2.c tool2.h main.c 

TAR = test
CC := gcc 
OBJ = main.o tool1.o tool2.o
RM = rm -r
CFLAGS += -Wall -c -o

# 最终目标
$(TAR):$(OBJ) 	# 目标文件:依赖文件
	$(CC) $(OBJ) -o $(TAR)

main.o:main.c 	# 目标文件:依赖文件
	$(CC) main.c $(CFLAGS) main.o

tool1.o:tool1.c # 目标文件:依赖文件
	$(CC) tool1.c $(CFLAGS) tool1.o

tool2.o:tool2.c	# 目标文件:依赖文件
	$(CC) tool2.c $(CFLAGS) tool2.o

.PHONY:
clean:
	$(RM) $(OBJ)  -r
cleanall:
	$(RM) $(OBJ) $(TAR) -r

```
# 第三层:
```
隐含规则 %.c %.o   任意.c、.o *.c *.o 所有.c、.o
```

```makefile
# tool1.c tool1.h tool2.c tool2.h main.c 

TAR=test
CC:=gcc 
OBJ=main.o tool1.o tool2.o
RM=rm -r
CFLAGS += -Wall -c -o

# 最终目标
$(TAR):$(OBJ) 	# 目标文件:依赖文件
	$(CC) $(OBJ) -o $(TAR)


%.o:%c	# 目标文件:依赖文件
	$(CC) %.c $(CFLAGS) %.o

.PHONY:
clean:
	$(RM) $(OBJ)  -r
cleanall:
	$(RM) $(OBJ) $(TAR) -r
```
# 第四层:
```
通配符 $^ 所有的目标文件 $@ 所有的依赖文件
```
```makefile
# tool1.c tool1.h tool2.c tool2.h main.c 

TAR=test
CC:=gcc 
OBJ=main.o tool1.o tool2.o
RM=rm -r
CFLAGS += -Wall -c -o

# 最终目标
$(TAR):$(OBJ) 	# 目标文件:依赖文件
	$(CC) $^ -o $@


%.o:%c	# 目标文件:依赖文件
	$(CC) $^ $(CFLAGS) $@

.PHONY:
clean:
	$(RM) $(OBJ)  -r
cleanall:
	$(RM) $(OBJ) $(TAR) -r
```

