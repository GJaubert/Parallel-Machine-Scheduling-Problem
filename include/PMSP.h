#ifndef PMSP
#define PMSP
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include "task.h"
#include "machine.h"
#include "mygreedy.h"
#include "greedy.h"
#include "gvns.h"
#include "grasp.h"

using table = std::vector<std::vector<int>>;
class Pmsp {
  private:
    int nTasks;
    int mMachines;
    int z_;
    int k_;
    std::vector<Machine> S;
    std::vector<Task> taskVector;
    table setupTime;
    std::shared_ptr<Strategy> algorithm_;
    int type_;
  public:
    /**
     * Constructor
     * @param string file name we want to read from
     * @param int algorithm we want to use 0: myGreedy, 1: Greedy, 2: Grasp, 3: GVNS
     */ 
    Pmsp(std::string fileName, int algorithm);
    /**
     * Copy constructor 
     * @param Pmsp 
     */ 
    Pmsp(Pmsp& inputObject); //constructor copia
    /**
     * Copy constructor for const object
     * @param Pmsp 
     */ 
    Pmsp(const Pmsp& inputObject);
    /**
     * Destructor 
     */ 
    ~Pmsp();
    /**
     * Loads all data from file
     * @param filename
     */ 
    void loadData(std::string fileName);
    /**
     * Getter for S
     * @return S
     */ 
    std::vector<Machine>& getS();
    /**
     * Getter for Task vector
     * @return S
     */ 
    std::vector<Task>& getTasks();
    /**
     * Getter for setup time table
     * @return S
     */
    std::vector<std::vector<int>> getSetupTime();
    /**
     * Check if all task has been visited
     * @return bool
     */
    bool allVisited();
    /**
     * Getter for M
     * @return M
     */
    int getM();
    /**
     * Getter for K
     * @return K
     */
    int getK();
    /**
     * Prints solution on console
     * @param int algorithm type for calculating Z
     * @param int execution time of algorithm 
     */
    void printSolution(int algorithmType, int time);
    /**
     * Computes solution for problem
     */
    void computeSolution();
    /**
     * Getter for Z
     * @return Z
     */
    int getZ();
    /**
     * Getter for Z using classic method
     * @return Z
     */
    int getZClassic();
    /**
     * Setter for K
     * @param K
     */
    void setK(int k);
    /**
     * Setter for type
     * @param type
     */
    void setType(int type);
    /**
     * Overload for operator =
     * @param K
     */
    Pmsp operator=(Pmsp& inputObject);
    /**
     * Overload for operator =
     * @param K
     */
    Pmsp operator=(const Pmsp& inputObject);
};

#endif