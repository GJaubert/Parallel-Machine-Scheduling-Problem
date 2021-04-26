#ifndef GRASP
#define GRASP
#define MOVEMENT_TYPES 8
#define ITERATIONS_LIMIT 3
#define IMPROVEMENT_LIMIT 1
#include "strategy.h"
#include "PMSP.h"
#include "movements.h"
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
  public: 
    virtual Pmsp computePmspSolution(Pmsp pmspObject);
    void construction(Pmsp& pmspObject);
    Pmsp getLocalOptimal(Pmsp pmspObject, int type);
    void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine, int kGrasp);
    void initialCase(std::vector<Task>& t, table setup, Machine& machine, KElement& newk, int machineIndex);
    void insertRandom(std::vector<Task>& t, std::vector<Machine>& machines, std::vector<KElement>& bestK);

    void printTitle(int type);
};

#endif