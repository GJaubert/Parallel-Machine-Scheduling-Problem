#ifndef MYGREEDY
#define MYGREEDY
#include "strategy.h"
#include "PMSP.h"
#include <chrono>

class MyGreedy : public Strategy {
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  int getMinTask(std::vector<Task>& t, table setup, int originTask);
  int getMinMachine(std::vector<Machine> m, table setup);
};

#endif