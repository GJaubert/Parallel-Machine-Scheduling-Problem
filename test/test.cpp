#include "../include/PMSP.h"

int main(int args, char* argv[]) {
  try {
    if (args <= 1)
      throw std::string("Error: argument required\n"); 
    // Pmsp problem(argv[1], 0);
    // problem.computeSolution();
    // std::cout << "--------------------------\n\n";
    // Pmsp problemGreedy(argv[1], 1);
    // problemGreedy.computeSolution();
    // std::cout << "--------------------------\n\n";
    std::cout << "|    ID  | ejecución | n | movimiento | TCT | CPU | límite iteraciones |\n";
    std::cout << "|------------|------------|---|-----------|-----|-----|---------------|\n";
    Pmsp problemGrasp(argv[1], 2);
    problemGrasp.computeSolution();
    // Pmsp problemGnvs(argv[1], 3);
    // problemGnvs.computeSolution();
    return 0;
  } catch(std::string err) {
    std::cout << err;
  }
}