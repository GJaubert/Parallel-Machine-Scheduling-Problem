#ifndef GVNS
#define GVNS
#include "strategy.h"
#include "grasp.h"
#include "PMSP.h"

class Gvns : public Strategy {
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  Pmsp getGraspSolution(Pmsp pmspObject);
  Pmsp Shake(Pmsp pmspObject);
  Pmsp Vnd(Pmsp pmspObject);
  void interMachineSwap(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position); //max: size - 1
};

#endif