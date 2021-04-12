#ifndef TASK
#define TASK
#include <vector>
#include <iostream>

class Task {
  private:
    int id_;
    int tct_;
    int processTime_;
    int setup_;
    bool visited_;
  public:
    Task();
    Task(int id, int processTime);
    ~Task();
    int getTaskTct();
    int getProcessTime();
    void setTctTime(int setupTime, int previousTime);
    void setVisited(bool state);
    bool getVisited();
    int getSetupTime();
    void setSetupTime(int time);
    int getId();
};

 #endif