CC=g++
#  $^ yilai
#  $@ mubiao
#  @buxianshi zhixing  -shibaibutingzhi
TARGET = first_make
LIBS = -lpthread
CXXFLAGS+=-std=c++11
CXXFLAGS+=-I ../test_gcc
OBJS = first_make.o xdata.o

$(TARGET):$(OBJS)
	-@rm test
	@echo "begin build $(TARGET)!"
	$(CC) $^ -o $@ $(LIBS) -std=c++11
	@echo "$(TARGET) build success!"

clear:
	rm first_make.o xdata.o first_make -rf