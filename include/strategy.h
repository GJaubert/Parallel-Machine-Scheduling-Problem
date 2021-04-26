#ifndef STRATEGY
#define STRATEGY
#define BIG_NUMBER 9999
#include <vector>

class Machine;
class Task;
class Pmsp;
using table = std::vector<std::vector<int>>;
class Strategy {
  public:
  /**
   * Function for computing the solution
   * @param Object Pmsp class object
   */ 
  virtual Pmsp computePmspSolution(Pmsp pmspObject) = 0;
};

#endif