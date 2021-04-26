#ifndef GVNS
#define GVNS
#define VND_MOVEMENTS_SET 0 //0: greedy search 1: lazy search
#define STOP_CONDITION 0 // 0: fixed_iteration 1: no improvement
#define KMAX 5
#define N_ITER_MAX 100
#define NO_IMPROVEMENT 50
#define BIG_NUMER 999999
#include "strategy.h"
#include "grasp.h"
#include "PMSP.h"
#include "movements.h"

class Gvns : public Strategy {
  /**
   * Function for computing the solution
   * @param Object Pmsp class object
   */ 
  virtual Pmsp computePmspSolution(Pmsp pmspObject);
  /**
   * Calculates a grasp solution for initialization phase
   * @param Object Pmsp class object
   * @return Pmsp Object
   */ 
  Pmsp getGraspSolution(Pmsp pmspObject);
  /**
   * Finds a new point in a bigger environment
   * @param Object Pmsp class object
   * @return Pmsp Object
   */  
  Pmsp Shake(Pmsp pmspObject);
  /**
   * Finds a local optimal
   * @param Object Pmsp class object
   * @return Pmsp Object
   */ 
  Pmsp Vnd(Pmsp pmspObject);
  /**
   * Calls the movement's function for searching an improvemed point
   * @param Object Pmsp class object
   * @return bool if there was improvement
   */ 
  bool selectMovement(Pmsp& pmspObject, int type);
};

#endif