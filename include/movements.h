#include "PMSP.h"

/**
 *  Inserts a task inside the same machine
 */
void intraMachineInsertion(std::vector<Task>& tasks, int taskPos, int position);
/**
 *  Inserts a task in other machine
 */
void interMachineInsertion(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position);
/**
 *  Swap two tasks inside the same machine
 */
void intraMachineSwap(std::vector<Task>& tasks, int taskPos, int position);
/**
 *  Swap two tasks from different machines
 */
void interMachineSwap(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position);
/**
 * Searchs one improvement in a greedy way using InterMachineInsert
 */
bool greedyImprovementInterMachineInsert(Pmsp& pmspObject);
/**
 * Searchs one improvement in a greedy way using IntraMachineInsert
 */
bool greedyImprovementIntraMachineInsert(Pmsp& pmspObject);
/**
 * Searchs one improvement in a greedy way using InterMachineSwap
 */
bool greedyImprovementInterMachineSwap(Pmsp& pmspObject);
/**
 * Searchs one improvement in a greedy way using IntraMachineSwa
 */
bool greedyImprovementIntraMachineSwap(Pmsp& pmspObject);
/**
 * Searchs one improvement in a lazy way using InterMachineInsert
 */
bool lazyImprovementInterMachineInsert(Pmsp& pmspObject);
/**
 * Searchs one improvement in a lazy way using IntraMachineInsert
 */ 
bool lazyImprovementIntraMachineInsert(Pmsp& pmspObject);
/**
 * Searchs one improvement in a lazy way using InterMachineSwap
 */ 
bool lazyImprovementInterMachineSwap(Pmsp& pmspObject);
/**
 * Searchs one improvement in a lazy way using IntraMachineSwap
 */ 
bool lazyImprovementIntraMachineSwap(Pmsp& pmspObject);