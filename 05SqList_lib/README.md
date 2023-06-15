# SeqList库的制作

### 静态库 

### 制作
```bash
gcc -c SeqList.c
ar -crv libSeqList.a SeqList.o
```

### 使用
```bash
gcc main.c -o mainStatic -static -L . -l SeqList
```

## 动态库 

### 制作
```bash
gcc -fPIC -shared -o libSeqList.so SeqList.c
```
### 使用
```bash
gcc main.c -o mainDynamic -L . -l SeqList
```