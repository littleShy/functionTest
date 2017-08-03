
BUILDDIR:=./build/
DEST:=$(BUILDDIR)functionTest
SOURCE:=functionInterface.cpp utility.cpp fileFunction.cpp pthreadFunction.cpp functionTest.cpp
#OBJECTS:=functionInterface.o utility.o fileFunction.o pthreadFunction.o functionTest.o
OBJECTS:=$(addprefix $(BUILDDIR), $(patsubst %.cpp, %.o, $(SOURCE)))

LFLAGS:=-lpthread
CXX:=g++
CC:=gcc

all: $(DEST)

$(DEST):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

#$(OBJECTS):%.o:%.cpp
#	$(CXX) -g -c $(LFLAGS) $^

$(OBJECTS):$(BUILDDIR)%.o:%.cpp
	$(CXX) -g -c $(LFLAGS) $^ -o $@

clean:
	$(RM) $(DEST) $(OBJECTS)

