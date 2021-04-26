#ifndef TASK
#define TASK
#include <vector>
#include <iostream>

class Task {
  private:
    int id_;
    int c_;
    int processTime_;
    int setup_;
    bool visited_;
  public:
    /**
     * Constructor
     */ 
    Task();
    /**
     * Constructor
     * @param int id for task
     * @param int process time of task
     */ 
    Task(int id, int processTime);
    /**
     * Desctructor
     */ 
    ~Task();
    /**
     * Getter for process time
     * @return process time
     */ 
    int getProcessTime();
    /**
     * Set if a task is visited
     * @return process time
     */ 
    void setVisited(bool state);
    /**
     * Getter for c
     * @return process time
     */
    int getTaskC();
    /**
     * Setter for c
     * @param setupTime
     * @param previousTime
     */
    void setCTime(int setupTime, int previousTime);
    /**
     * Check if a task has been visited
     * @return bool
     */
    bool getVisited();
    /**
     * Gets setup time for a task
     * @return int setup time
     */
    int getSetupTime();
    /**
     * Setter for setup time
     * @param setupTime
     */
    void setSetupTime(int time);
    /**
     * Getter for id
     * @return id
     */
    int getId();
};

 #endif