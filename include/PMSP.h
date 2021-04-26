#ifndef PMSP
#define PMSP
#define K 2
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
    Pmsp(std::string fileName, int algorithm);
    Pmsp(Pmsp& inputObject); //constructor copia
    Pmsp(const Pmsp& inputObject);
    ~Pmsp();
    void loadData(std::string fileName);
    std::vector<Machine>& getS();
    std::vector<Task>& getTasks();
    std::vector<std::vector<int>> getSetupTime();
    bool allVisited();
    int getM();
    int getK();
    void printSolution(int algorithmType, int time);
    void computeSolution();
    int getZ();
    int getZClassic();
    void setType(int type);
    Pmsp operator=(Pmsp& inputObject);
    Pmsp operator=(const Pmsp& inputObject);
};

#endif