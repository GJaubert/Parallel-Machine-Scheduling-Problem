#ifndef GREEDY
#define GREEDY
#include "strategy.h"
#include "PMSP.h"

class Greedy : public Strategy {
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine);
};

#endif