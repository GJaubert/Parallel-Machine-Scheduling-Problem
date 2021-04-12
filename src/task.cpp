#include "../include/task.h"

Task::Task() {
  visited_ = false;
  processTime_ = 0;
  setup_ = 0;
  c_ = 0;
}

Task::Task(int id, int processTime) {
  id_ = id;
  processTime_ = processTime;
  visited_ = false;
  c_ = 0;
}

Task::~Task() {}

int Task::getProcessTime() {
  return processTime_;
}

void Task::setVisited(bool state) {
  visited_ = state;
}

void Task::setCTime(int setupTime, int previousTime) {
  c_ = setupTime + previousTime + processTime_;
}

int Task::getTaskC() {
  return c_;
}

bool Task::getVisited() {
  return visited_;
}

int Task::getId() {
  return id_;
}

int Task::getSetupTime() {
  return setup_;
}

void Task::setSetupTime(int time) {
  setup_ = time;
}