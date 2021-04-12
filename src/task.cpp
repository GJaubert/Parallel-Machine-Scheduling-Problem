#include "../include/task.h"

Task::Task() {
  visited_ = false;
  processTime_ = 0;
  tct_ = 0;
}

Task::Task(int id, int processTime) {
  id_ = id;
  processTime_ = processTime;
  visited_ = false;
  tct_ = 0;
}

Task::~Task() {}

int Task::getProcessTime() {
  return processTime_;
}

void Task::setVisited() {
  visited_ = true;
}

void Task::setTctTime(int setupTime, int previousTime) {
  tct_ = setupTime + previousTime + processTime_;
  // std::cout << "\ntct " << tct_ << " ";
  // std::cout << "setup " << setupTime << " ";
  // std::cout << "prevT " << previousTime << " ";
  // std::cout << "process" << processTime_ << "\n";
}

int Task::getTaskTct() {
  return tct_;
}

bool Task::getVisited() {
  return visited_;
}

int Task::getId() {
  return id_;
}