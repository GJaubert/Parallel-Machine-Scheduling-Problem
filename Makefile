CXX = g++ -O3
#CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g -fsanitize=address
#LDFLAGS =  -fsanitize=address

SRC = ./src/main.cpp ./src/PMSP.cpp ./src/task.cpp ./src/machine.cpp ./src/mygreedy.cpp ./src/greedy.cpp ./src/grasp.cpp ./src/gvns.cpp ./src/movements.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = bin/main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf $(OBJ) $(EXEC)
