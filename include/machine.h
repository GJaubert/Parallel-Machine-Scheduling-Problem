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
    /**
     * Constructor
     */ 
    Machine();
    /**
     * Destructor
     */ 
    ~Machine();
    /**
     * Getter for tasks vector
     * @return tasks vector
     */ 
    std::vector<Task>& getTasks();
    /**
     * Calculates the machine's TCT
     * @return TCT
     */ 
    int getTct();
    /**
     * Changes the machine's TCT
     * @param time
     */ 
    void updateTct(int time);
    /**
     * Calculates the machine's TCT with classic algorithm
     * @param table setup time table
     * @return TCT
     */
    int getTctClassic(std::vector<std::vector<int>> setupTable);
    /**
     * Calculates the machine's TCT with a given task
     * @param position of new task
     * @param table setup time table
     * @return TCT
     */
    int predictTct(Task t, int position, std::vector<std::vector<int>> setupTime);
};

#endif