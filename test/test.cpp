#include <chrono>
#include "../include/PMSP.h"
using namespace std::chrono;

int main(int args, char* argv[]) {
  try {
    if (args <= 1)
      throw std::string("Error: argument required\n"); 
    Pmsp problem(argv[1], 2);
    auto start = high_resolution_clock::now();
    problem.computeSolution();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    problem.printSolution(1);
    std::cout << "tiempo " << duration.count() << "ms" << "\n";
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}