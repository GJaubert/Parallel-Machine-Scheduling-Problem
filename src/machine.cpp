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
  int i = 0;
  if (tasks.size() > 0) {
    tct_ = k * (tasks[0].getProcessTime() + setupTime[0][tasks[0].getId()]);
    k--;
  }
  for (int i = 1; i < tasks.size(); i++) {
    tct_ += k * (tasks[i].getProcessTime() + setupTime[tasks[i - 1].getId()][tasks[i].getId()]);
    k--;
  }
  return tct_;
}

int Machine::predictTct(Task t, int position, std::vector<std::vector<int>> setupTime) {
  //std::cout << "Predict: " << "\n";
  int k = tasks.size() + 1;
  tct_ = 0;
  if (tasks.size() == 0) {
    tct_ = t.getProcessTime() + setupTime[0][t.getId()];
  }
  if (tasks.size() > 0) {
    if (position == 0) {
      tct_ += k * (t.getProcessTime() + setupTime[0][t.getId()]);
      k--;
      //std::cout << "from: " << 0 << " to: " << t.getId() << " tct: " << tct_ << "\n";
      tct_ += k * (tasks[0].getProcessTime() + setupTime[t.getId()][tasks[0].getId()]);
      //std::cout << "from: " << t.getId() << " to: " << tasks[0].getId() << " tct: " << tct_ << "\n";
      k--;
    } else {
      tct_ += k * (tasks[0].getProcessTime() + setupTime[0][tasks[0].getId()]);
      //std::cout << "from: " << 0 << " to: " << tasks[0].getId() << " tct: " << tct_ << "\n";
      k--;
    }
  }
  for (int i = 1; i < tasks.size(); i++) {
    if (position == i) {
      tct_ += k * (t.getProcessTime() + setupTime[tasks[i - 1].getId()][t.getId()]);
      //std::cout << "from: " << tasks[i - 1].getId() << " to: " << t.getId() << " tct: " << tct_ << "\n";
      k--;
      tct_ += k * (tasks[i].getProcessTime() + setupTime[t.getId()][tasks[i].getId()]);
      //std::cout << "from: " << t.getId() << " to: " << tasks[i].getId() << " tct: " << tct_ << "\n";
      k--;
    } else {
      tct_ += k * (tasks[i].getProcessTime() + setupTime[tasks[i - 1].getId()][tasks[i].getId()]);
        //std::cout << "from: " << tasks[i - 1].getId() << " to: " << tasks[i].getId() << " tct: " << tct_ << "\n";
      k--;
    }
  }
  if (position == tasks.size()) {
    tct_ += k * (t.getProcessTime() + setupTime[tasks[tasks.size() - 1].getId()][t.getId()]);
    //std::cout << "from: " << tasks[tasks.size() - 1].getId() << " to: " << t.getId() << " tct: " << tct_ << "\n";
    k--;
  }
  return tct_;
}