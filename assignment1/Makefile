SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)
EXEC:=assignment1
CC:=gcc
CXX:=g++
CFLAGS:=`pkg-config --cflags gl` -ggdb -O3
CXXFLAGS:=$(CFLAGS)
LDFLAGS:=`pkg-config --libs gl`
LIBS:=-lglut -lm

$(EXEC):$(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm -f $(OBJ)
	
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	
