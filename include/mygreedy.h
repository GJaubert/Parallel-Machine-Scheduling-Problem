#ifndef MYGREEDY
#define MYGREEDY
#include "strategy.h"
#include "PMSP.h"
#include <chrono>

class MyGreedy : public Strategy {
  /**
   * Function for computing the solution
   * @param Object Pmsp class object
   */ 
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  /**
   * Gets the task with less increase on the TCT
   * @param vector task vector
   * @param table table that storages setup times
   * @param int origin task
   */ 
  int getMinTask(std::vector<Task>& t, table setup, int originTask);
  /**
   * Gets the task with less increase on the TCT
   * @param vector machine vector
   * @param table table that storages setup times
   * @return position of minimal machine
   */ 
  int getMinMachine(std::vector<Machine> m, table setup);
};

#endif