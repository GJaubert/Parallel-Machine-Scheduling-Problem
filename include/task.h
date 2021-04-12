#ifndef TASK
#define TASK
#include <vector>
#include <iostream>

class Task {
  private:
    int id_;
    int tct_;
    int processTime_;
    bool visited_;
  public:
    Task();
    Task(int id, int processTime);
    ~Task();
    int getTaskTct();
    int getProcessTime();
    void setTctTime(int setupTime, int previousTime);
    void setVisited();
    bool getVisited();
    int getId();
};

 #endif