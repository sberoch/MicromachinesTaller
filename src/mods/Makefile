CC_DL = g++ --std=c++11
CC = $(CC_DL) -pedantic-errors

.PHONY: all clean run

Plugin1.so: Plugin1.cpp
	$(CC_DL) -fPIC -rdynamic -shared -o Plugin1.so Plugin1.cpp

Plugin2.so: Plugin2.cpp
	$(CC_DL) -fPIC -rdynamic -shared -o Plugin2.so Plugin2.cpp

clean:
	rm -rf *.o *.a *.so *.out
