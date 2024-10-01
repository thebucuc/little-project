CC = g++
CFLAGS = -Wall -g -lm -std=c++2a
 

main: main.o arg_parse.o file_processor.o thread_pool.o
	$(CC) $(CFLAGS) -o main main.o arg_parse.o file_processor.o thread_pool.o -lstdc++fs -lpthread

main.o: main.cpp arg_parse.h file_processor.h thread_pool.h
	$(CC) $(CFLAGS) -c main.cpp 

arg_parse.o: arg_parse.h 
	$(CC) $(CFLAGS) -c arg_parse.cpp 

thread_pool.o: file_processor.h thread_pool.h thread_pool.cpp
	$(CC) $(CFLAGS) -c thread_pool.cpp -lpthread

file_processor.o: file_processor.h arg_parse.h file_processor.cpp
	$(CC) $(CFLAGS) -c file_processor.cpp



