#ifndef GREEDY
#define GREEDY
#include "strategy.h"
#include "PMSP.h"

class Greedy : public Strategy {
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  int getMinTask(std::vector<Task>& t, table setup, int& tmpTaskValue, std::vector<Machine>& machine);
  int getMinMachine(std::vector<Machine> m);
};

#endif