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
    totalTct += tasks[i].getTaskTct();
  } 
  return totalTct;
}

void Machine::updateTct(int time) {
  tct_ = time + tct_;
  //std::cout << "set: " << tct_ << "\n"; 
}