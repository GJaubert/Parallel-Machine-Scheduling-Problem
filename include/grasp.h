#ifndef GRASP
#define GRASP
#include "strategy.h"
#include "PMSP.h"
#include <time.h>
#include <stdlib.h>

class Grasp : public Strategy {
  struct KElement {
    int i_;
    int j_;
    int k_;
  };
  virtual std::vector<Machine> computePmspSolution(Pmsp pmspObject);
  void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine, int kGrasp);
  void initialCase(std::vector<Task>& t, table setup, Machine& machine, KElement& newk, int machineIndex);
  void insertRandom(std::vector<Task>& t, std::vector<Machine>& machines, std::vector<KElement>& bestK);
};

#endif