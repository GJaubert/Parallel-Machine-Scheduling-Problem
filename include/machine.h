#ifndef MACHINE
#define MACHINE
#include <vector>
#include <iostream>
#include "task.h"

class Machine {
  private:
    std::vector<Task> tasks;
    int tct_;
  public:
    Machine();
    ~Machine();
    std::vector<Task>& getTasks();
    int getTct();
    void updateTct(int time);
};

#endif