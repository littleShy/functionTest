DEST:=functionTest


OBJECTS:=functionInterface.o utility.o fileFunction.o pthreadFunction.o functionTest.o
LFLAGS:=-lpthread
CXX:=g++
CC:=gcc

all: $(DEST)

$(DEST):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJECTS):%.o:%.cpp
	$(CXX) -g -c $(LFLAGS) $^

clean:
	$(RM) $(DEST) $(OBJECTS)

