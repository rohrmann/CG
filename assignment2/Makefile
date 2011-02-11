SRC:=$(wildcard *.cpp)
OBJ:=$(SRC:.cpp=.o)
EXEC:=assignment2
CC:=clang
CXX:=clang++
CFLAGS:=`pkg-config --cflags gl` -g -O3
CXXFLAGS:=$(CFLAGS)
LDFLAGS:=`pkg-config --libs gl`
LIBS:=-lglut -lm

$(EXEC):$(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)
	
clean:
	rm -f $(OBJ)
	
%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $<
	
