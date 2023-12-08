CXX := g++
CXXFLAGS += -std=c++20 -g -O2 -Wall -Wextra -Werror 

SRC := $(wildcard ??.cpp)
ALL := $(SRC:%.cpp=%)

all: $(ALL)
	for d in $^ ; do echo "=== Day $$d ===" ; ./$$d < $$d.in; done

clean:
	$(RM) $(ALL)
