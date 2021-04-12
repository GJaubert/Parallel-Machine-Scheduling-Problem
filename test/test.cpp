#include "../include/PMSP.h"

int main(int args, char* argv[]) {
  try {
    if (args <= 1)
      throw std::string("Error: argument required\n"); 
    Pmsp problem(argv[1], 0);
    problem.computeSolution();
    problem.printSolution(1);
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}