
all: test

test: test.o
	g++ -lpthread -o test test.o

test.o: test.cpp
	g++ -c test.cpp

clean:
	rm -rf test *.o
