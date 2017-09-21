
BUILDDIR:=./build/
DEST:=$(BUILDDIR)main
SOURCE:= utility.cpp functionInterface.cpp fileFunction.cpp pthreadFunction.cpp sortFunction.cpp dataStructure.cpp functionTest.cpp main.cpp
#OBJECTS:=functionInterface.o utility.o fileFunction.o pthreadFunction.o functionTest.o
OBJECTS:=$(addprefix $(BUILDDIR), $(patsubst %.cpp, %.o, $(SOURCE)))

LFLAGS:=-mcmodel=large
SHARED_LIBS:=-lpthread
CXX:=g++
CC:=gcc

$(shell mkdir -p $(BUILDDIR))

all: $(DEST)

$(DEST):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

dataStructure.cpp: linearList.h chain.h

$(OBJECTS):$(BUILDDIR)%.o:%.cpp
	$(CXX) -g -c $(LFLAGS) $(SHARED_LIBS) $^ -o $@

clean:
	$(RM) -rf $(DEST) $(OBJECTS) # $(BUILDDIR)

