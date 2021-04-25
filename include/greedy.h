#ifndef GREEDY
#define GREEDY
#include "strategy.h"
#include "PMSP.h"
#include <chrono>

class Greedy : public Strategy {
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine);
};

#endif