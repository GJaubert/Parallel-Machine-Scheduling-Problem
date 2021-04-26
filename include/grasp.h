#ifndef GRASP
#define GRASP
#define MOVEMENT_TYPES 8
#define ITERATIONS_LIMIT 3
#define IMPROVEMENT_LIMIT 10
#define K 2
#include "strategy.h"
#include "PMSP.h"
#include "movements.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <chrono>

class Grasp : public Strategy {
  /**
   * This structure is used for saving data about a certain task
   */
  struct KElement {
    int i_;
    int j_;
    int k_;
  };
  public: 
    /**
     * Function for computing the solution
     * @param Object Pmsp class object
     */ 
    virtual Pmsp computePmspSolution(Pmsp pmspObject);
    /**
     * Construction phase of Grasp algorithm
     * @param Object Pmsp class object
     */ 
    void construction(Pmsp& pmspObject);
    /**
     * Calculates local optimal given a point
     * @param Object Pmsp class object
     * @param int type - Function we want to use to search loacl optimal
     */ 
    Pmsp getLocalOptimal(Pmsp pmspObject, int type);
    /**
     * Gets the task with less increase on the TCT
     * @param vector task vector
     * @param table table that storages setup times
     * @param vector machine vector
     * @param int k value for grasp algorithm
     * @return Pmsp object
     */ 
    void getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machine, int kGrasp);
    /**
     * Initialization of construction phase
     * @param vector task vector
     * @param table table that storages setup times
     * @param vector machine vector
     * @param struct new element we want to introduce
     * @param int index indicating the current machine
     */ 
    void initialCase(std::vector<Task>& t, table setup, Machine& machine, KElement& newk, int machineIndex);
    /**
     * Inserts random task from k elements vector
     * @param vector task vector
     * @param vector machine vector
     * @param vector vector of best k elements
     */ 
    void insertRandom(std::vector<Task>& t, std::vector<Machine>& machines, std::vector<KElement>& bestK);
    /**
     * Prints title for a specific movement
     * @param type type of movement we want to print
     */ 
    void printTitle(int type);
};

#endif