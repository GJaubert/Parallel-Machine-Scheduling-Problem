CXX = g++ -O2
#CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address

SRC = ./test/test.cpp ./src/PMSP.cpp ./src/task.cpp ./src/machine.cpp ./src/mygreedy.cpp ./src/greedy.cpp ./src/grasp.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
