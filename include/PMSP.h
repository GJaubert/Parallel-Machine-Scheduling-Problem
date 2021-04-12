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

using table = std::vector<std::vector<int>>;
class Pmsp {
  private:
    int nTasks;
    int mMachines;
    int z_;
    std::vector<Machine> S;
    std::vector<Task> taskVector;
    table setupTime;
    std::shared_ptr<Strategy> algorithm_;
  public:
    Pmsp(std::string fileName, int algorithm);
    ~Pmsp();
    void loadData(std::string fileName);
    std::vector<Machine>& getS();
    std::vector<Task>& getTasks();
    std::vector<std::vector<int>> getSetupTime();
    bool allVisited();
    int getM();
    void printSolution(int algorithmType);
    void computeSolution();
    int getZ();
    int getZClassic();
};

#endif