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
    int getTctClassic(std::vector<std::vector<int>> setupTable);
    int predictTct(Task t, int position, std::vector<std::vector<int>> setupTime);
};

#endif