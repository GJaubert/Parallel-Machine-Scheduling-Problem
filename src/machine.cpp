#include "../include/machine.h"

Machine::Machine() {
  tct_ = 0;
}

Machine::~Machine() {}

std::vector<Task>& Machine::getTasks() {
  return tasks;
}

int Machine::getTct() {
  int totalTct = 0;
  for (int i = 0; i < tasks.size(); i++) {
    totalTct += tasks[i].getTaskC();
  } 
  return totalTct;
}

void Machine::updateTct(int time) {
  tct_ = time + tct_;
}

int Machine::getTctClassic(std::vector<std::vector<int>> setupTime) {
  int k = tasks.size();
  tct_ = 0;
  if (tasks.size() > 0) {
    tct_ += k * (tasks[0].getProcessTime() + setupTime[0][tasks[0].getId()]);
    k--;
  }
  for (int i = 1; i < tasks.size(); i++) {
    tct_ += k * (tasks[i].getProcessTime() + setupTime[tasks[i - 1].getId()][tasks[i].getId()]);
      //std::cout << "from: " << tasks[i - 1].getId() << " to: " << tasks[i].getId() << " tct: " << tct_ << "\n";
    k--;
  }
  return tct_;
}