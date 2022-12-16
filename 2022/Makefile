CXX := g++
CXXFLAGS += -std=c++20 -g -O2

SRC := $(wildcard *.cpp)
ALL := $(SRC:%.cpp=%)

all: $(ALL)
	for d in $^ ; do echo "=== Day $$d ===" ; ./$$d < $$d.in1; done

clean:
	$(RM) $(ALL)
