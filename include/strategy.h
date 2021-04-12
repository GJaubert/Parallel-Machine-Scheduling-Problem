#ifndef STRATEGY
#define STRATEGY
#include <vector>

class Machine;
class Task;
class Pmsp;
using table = std::vector<std::vector<int>>;
class Strategy {
  public:
    virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject) = 0;
};

#endif