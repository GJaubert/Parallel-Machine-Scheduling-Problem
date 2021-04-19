#ifndef GRASP
#define GRASP
#define MOVEMENT_TYPES 8
#define ITERATIONS_LIMIT 5
#define IMPROVEMENT_LIMIT 3
#include "strategy.h"
#include "PMSP.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>

class Grasp : public Strategy {
  struct KElement {
    int i_;
    int j_;
    int k_;
  };
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  void construction(Pmsp& pmspObject);
  Pmsp getLocalOptimal(Pmsp pmspObject, int type);
  void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine, int kGrasp);
  void initialCase(std::vector<Task>& t, table setup, Machine& machine, KElement& newk, int machineIndex);
  void insertRandom(std::vector<Task>& t, std::vector<Machine>& machines, std::vector<KElement>& bestK);
  void intraMachineInsertion(std::vector<Task>& tasks, int taskPos, int position); //solo puede como max: size - 1
  void interMachineInsertion(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position);//como max size
  void intraMachineSwap(std::vector<Task>& tasks, int taskPos, int position); // max: sie - 1
  void interMachineSwap(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position); //max: size - 1
  bool greedyImprovementInterMachineInsert(Pmsp& pmspObject);
  bool greedyImprovementIntraMachineInsert(Pmsp& pmspObject);
  bool greedyImprovementInterMachineSwap(Pmsp& pmspObject);
  bool greedyImprovementIntraMachineSwap(Pmsp& pmspObject);
  bool lazyImprovementInterMachineInsert(Pmsp& pmspObject);
  bool lazyImprovementIntraMachineInsert(Pmsp& pmspObject);
  bool lazyImprovementInterMachineSwap(Pmsp& pmspObject);
  bool lazyImprovementIntraMachineSwap(Pmsp& pmspObject);
  void printTitle(int type);
};

#endif