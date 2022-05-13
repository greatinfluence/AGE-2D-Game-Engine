CXX = g++
CXXFLAGS = -std=c++14 -Wall
LDFLAGS = -lncurses
EXEC = ../arlg
SRC = $(wildcard *.cc)
SRC += $(wildcard engine/*.cc)
OBJECTS = $(patsubst %cc, %o, $(SRC))

${EXEC}: ${OBJECTS}
	$(CXX) ${OBJECTS} -o ${EXEC} ${CXXFLAGS} ${LDFLAGS}

%.o:%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm $(EXEC) $(OBJECTS)
