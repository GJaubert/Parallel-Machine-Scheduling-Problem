#ifndef GREEDY
#define GREEDY
#include "strategy.h"
#include "PMSP.h"
#include <chrono>

class Greedy : public Strategy {
  /**
   * Function for computing the solution
   * @param Object Pmsp class object
   */ 
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
    /**
   * Gets the task with less increase on the TCT
   * @param vector task vector
   * @param table table that storages setup times
   * @param vector machine vector
   */ 
  void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine);
};

#endif