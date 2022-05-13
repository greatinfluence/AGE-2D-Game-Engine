CXX = g++
CXXFLAGS = -std=c++14 -Wall

src = $(wildcard *.cc)
target = $(patsubst %.cc, %.o, ${src})

.PHONY: all clean

%.o:%.cc
	$(CXX) ${CXXFLAGS} -c  $< -o $@

all: ${target}

clean:
	rm -f ${target}
