DEST:functionTest
OBJECTS:=functionTest.o
LFLAGS:=-lpthread
CXX:=g++
CC:=gcc

all: $(DEST)

$(OBJECTS):%.o:%.cpp
	echo $< $^
	$(CXX) $(LFLAGS) $< -o $@

$(OBJECTS): inc.h functionInterface.h utility.h fileFunction.h

clean:
	$(RM) $(DEST) $(OBJECTS)

