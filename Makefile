CC = gcc
CXX = g++
CFLAGS = -Wall -Wextra -std=c99 -I./18_C
CXXFLAGS = -Wall -Wextra -std=c++11 -I./18_CPP

all: c_prog cpp_prog cross_test

c_prog: 18_C/18.o 18_C/18_test.o
	$(CC) $(CFLAGS) -o run_c 18_C/18.o 18_C/18_test.o

18_C/18.o: 18_C/18.c 18_C/18.h
	$(CC) $(CFLAGS) -c 18_C/18.c -o 18_C/18.o

18_C/18_test.o: 18_C/18_test.c 18_C/18.h
	$(CC) $(CFLAGS) -c 18_C/18_test.c -o 18_C/18_test.o

cpp_prog: 18_CPP/Image.o 18_CPP/18_test.o
	$(CXX) $(CXXFLAGS) -o run_cpp 18_CPP/Image.o 18_CPP/18_test.o

18_CPP/Image.o: 18_CPP/Image.cpp 18_CPP/Image.h
	$(CXX) $(CXXFLAGS) -c 18_CPP/Image.cpp -o 18_CPP/Image.o

18_CPP/18_test.o: 18_CPP/18_test.cpp 18_CPP/Image.h
	$(CXX) $(CXXFLAGS) -c 18_CPP/18_test.cpp -o 18_CPP/18_test.o

cross_test: 18_CPP/18_cross_test.cpp 18_C/18.o 18_CPP/Image.o
	$(CXX) $(CXXFLAGS) -I./18_C -o run_cross 18_CPP/18_cross_test.cpp 18_C/18.o 18_CPP/Image.o

clean:
	rm -f 18_C/*.o 18_CPP/*.o run_c run_cpp run_cross *.bmp