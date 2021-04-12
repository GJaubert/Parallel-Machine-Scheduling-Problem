#ifndef MYGREEDY
#define MYGREEDY
#include "strategy.h"
#include "PMSP.h"

class MyGreedy : public Strategy {
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  int getMinTask(std::vector<Task>& t, table setup, int originTask);
  int getMinMachine(std::vector<Machine> m);
};

#endif