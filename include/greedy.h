#ifndef GREEDY
#define GREEDY
#include "strategy.h"
#include "PMSP.h"

class Greedy : public Strategy {
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  int getMinTask(std::vector<Task>& t, table setup, int originTask);
  int getMinMachine(std::vector<Machine> m);
};

#endif