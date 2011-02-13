SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)
EXEC:=textures
CC:=gcc
CXX:=g++
CFLAGS:=`pkg-config --cflags gl` -g
CXXFLAGS:=$(CFLAGS)
LDFLAGS:=`pkg-config --libs gl`
LIBS:=-lglut -lm

$(EXEC):$(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm -f $(OBJ)
	
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	
