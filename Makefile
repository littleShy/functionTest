DEST:=functionTest

OBJECTS:=functionTest.o
LFLAGS:=-lpthread
CXX:=g++
CC:=gcc

all: $(DEST)

$(DEST):$(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(OBJECTS):%.o:%.cpp
	@echo ':' $< '|' $^
	$(CXX) -c $(LFLAGS) $<

$(OBJECTS): inc.h functionInterface.h utility.h fileFunction.h

clean:
	$(RM) $(DEST) $(OBJECTS)

