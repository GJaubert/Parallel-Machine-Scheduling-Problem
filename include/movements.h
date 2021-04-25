#include "PMSP.h"

void intraMachineInsertion(std::vector<Task>& tasks, int taskPos, int position); //solo puede como max: size - 1
void interMachineInsertion(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position);//como max size
void intraMachineSwap(std::vector<Task>& tasks, int taskPos, int position); // max: sie - 1
void interMachineSwap(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position); //max: size - 1
bool greedyImprovementInterMachineInsert(Pmsp& pmspObject);
bool greedyImprovementIntraMachineInsert(Pmsp& pmspObject);
bool greedyImprovementInterMachineSwap(Pmsp& pmspObject);
bool greedyImprovementIntraMachineSwap(Pmsp& pmspObject);
bool lazyImprovementInterMachineInsert(Pmsp& pmspObject);
bool lazyImprovementIntraMachineInsert(Pmsp& pmspObject);
bool lazyImprovementInterMachineSwap(Pmsp& pmspObject);
bool lazyImprovementIntraMachineSwap(Pmsp& pmspObject);