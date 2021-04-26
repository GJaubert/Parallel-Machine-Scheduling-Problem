#ifndef GVNS
#define GVNS
#define VND_MOVEMENTS_SET 0
#define KMAX 5
#define N_ITER_MAX 1000
#define BIG_NUMER 999999
#include "strategy.h"
#include "grasp.h"
#include "PMSP.h"
#include "movements.h"

class Gvns : public Strategy {
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  Pmsp getGraspSolution(Pmsp pmspObject);
  Pmsp Shake(Pmsp pmspObject);
  Pmsp Vnd(Pmsp pmspObject);
  bool selectMovement(Pmsp& pmspObject, int type);
  void interMachineSwap(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position); //max: size - 1
};

#endif