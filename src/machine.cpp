#include "../include/machine.h"

Machine::Machine() {
  tct_ = 0;
}

Machine::~Machine() {}

std::vector<Task>& Machine::getTasks() {
  return tasks;
}

int Machine::getTct() {
  //std::cout << "get: " << tct_ << "\n"; 
  int totalTct = 0;
  for (int i = 0; i < tasks.size(); i++) {
    totalTct += tasks[i].getTaskC();
  } 
  return totalTct;
}

void Machine::updateTct(int time) {
  tct_ = time + tct_;
  //std::cout << "set: " << tct_ << "\n"; 
}

int Machine::getTctClassic(std::vector<std::vector<int>> setupTime) {
  int k = tasks.size();
  tct_ = 0;
  if (tasks.size() > 0) {
    tct_ += k * (tasks[0].getProcessTime() + setupTime[0][tasks[0].getId()]);
    //std::cout << "tct: " << tct_ <<" process: " << tasks[0].getProcessTime() << " setup " << setupTime[tasks[0].getId()][tasks[0].getId()] << " k " << k << "\n";
    k--;
  }
  for (int i = 1; i < tasks.size(); i++) {
    tct_ += k * (tasks[i].getProcessTime() + setupTime[tasks[i - 1].getId()][tasks[i].getId()]);
    //std::cout << "tct: " << tct_ <<" process: " << tasks[i].getProcessTime() << " setup " << setupTime[tasks[i - 1].getId()][tasks[i].getId()] << " k " << k << "\n";
    k--;
  }
  // for (int i = 1; i < tasks.size(); i++) {
  //   tct_ += k * (tasks[i].getProcessTime() + tasks[i].getSetupTime());
  //   k--;
  // }
  return tct_;
}