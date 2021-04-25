#include "../include/movements.h"

bool greedyImprovementInterMachineInsert(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingM = 0; tryingM < pmspObject.getS().size(); tryingM++) {
        if (tryingM == machineIndex) {
          continue;
        }
        for (int tryingT = 0; tryingT <= pmspObject.getS().at(tryingM).getTasks().size(); tryingT++) {
          interMachineInsertion(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(tryingM).getTasks(), current, tryingT);
          tmpZ = pmspObject.getZClassic();
          if (tmpZ < bestZ) {
            bestPmsp = pmspObject;
            bestZ = tmpZ;
          }
          pmspObject = currentPmsp;
        }
      }
    }
  }
  improved = (bestZ < currentZ) ? true : false;
  pmspObject = bestPmsp;
  return improved;
}

bool greedyImprovementInterMachineSwap(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingM = 0; tryingM < pmspObject.getS().size(); tryingM++) {
        if (tryingM == machineIndex) {
          continue;
        }
        for (int tryingT = 0; tryingT < pmspObject.getS().at(tryingM).getTasks().size(); tryingT++) {
          interMachineSwap(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(tryingM).getTasks(), current, tryingT);
          tmpZ = pmspObject.getZClassic();
          if (tmpZ < bestZ) {
            bestPmsp = pmspObject;
            bestZ = tmpZ;
          }
          pmspObject = currentPmsp;
        }
      }
    }
  }
  improved = (bestZ < currentZ) ? true : false;
  pmspObject = bestPmsp;
  return improved;
}

bool greedyImprovementIntraMachineInsert(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingT = 0; tryingT < pmspObject.getS().at(machineIndex).getTasks().size(); tryingT++) {
        intraMachineInsertion(pmspObject.getS().at(machineIndex).getTasks(), current, tryingT);
        tmpZ = pmspObject.getZClassic();
        if (tmpZ < bestZ) {
          bestPmsp = pmspObject;
          bestZ = tmpZ;
        }
        pmspObject = currentPmsp;
      }
    }
  }
  improved = (bestZ < currentZ) ? true : false;
  pmspObject = bestPmsp;
  return improved;
}

bool greedyImprovementIntraMachineSwap(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingT = 0; tryingT < pmspObject.getS().at(machineIndex).getTasks().size(); tryingT++) {
        intraMachineSwap(pmspObject.getS().at(machineIndex).getTasks(), current, tryingT);
        tmpZ = pmspObject.getZClassic();
        if (tmpZ < bestZ) {
          bestPmsp = pmspObject;
          bestZ = tmpZ;
        }
        pmspObject = currentPmsp;
      }
    }
  }
  improved = (bestZ < currentZ) ? true : false;
  pmspObject = bestPmsp;
  return improved;
}

bool lazyImprovementInterMachineInsert(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingM = 0; tryingM < pmspObject.getS().size(); tryingM++) {
        if (tryingM == machineIndex) {
          continue;
        }
        for (int tryingT = 0; tryingT <= pmspObject.getS().at(tryingM).getTasks().size(); tryingT++) {
          interMachineInsertion(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(tryingM).getTasks(), current, tryingT);
          tmpZ = pmspObject.getZClassic();
          if (tmpZ < bestZ) {
            bestPmsp = pmspObject;
            bestZ = tmpZ;
            return true;
          }
          pmspObject = currentPmsp;
        }
      }
    }
  }
  pmspObject = bestPmsp;
  return false;
}

bool lazyImprovementIntraMachineInsert(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingT = 0; tryingT < pmspObject.getS().at(machineIndex).getTasks().size(); tryingT++) {
        intraMachineInsertion(pmspObject.getS().at(machineIndex).getTasks(), current, tryingT);
        tmpZ = pmspObject.getZClassic();
        if (tmpZ < bestZ) {
          bestPmsp = pmspObject;
          bestZ = tmpZ;
          return true;
        }
        pmspObject = currentPmsp;
      }
    }
  }
  pmspObject = bestPmsp;
  return false;
}

bool lazyImprovementInterMachineSwap(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingM = 0; tryingM < pmspObject.getS().size(); tryingM++) {
        if (tryingM == machineIndex) {
          continue;
        }
        for (int tryingT = 0; tryingT < pmspObject.getS().at(tryingM).getTasks().size(); tryingT++) {
          interMachineSwap(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(tryingM).getTasks(), current, tryingT);
          tmpZ = pmspObject.getZClassic();
          if (tmpZ < bestZ) {
            bestPmsp = pmspObject;
            bestZ = tmpZ;
            return true;
          }
          pmspObject = currentPmsp;
        }
      }
    }
  }
  pmspObject = bestPmsp;
  return false;
}

bool lazyImprovementIntraMachineSwap(Pmsp& pmspObject) {
  Pmsp currentPmsp(pmspObject);
  Pmsp bestPmsp(pmspObject);
  bool improved = false;
  int currentZ = bestPmsp.getZClassic();
  int bestZ = currentZ;
  int tmpZ = 0;
  for (int machineIndex = 0; machineIndex < pmspObject.getS().size(); machineIndex++) {
    for (int current = 0; current < pmspObject.getS().at(machineIndex).getTasks().size(); current++) {
      for (int tryingT = 0; tryingT < pmspObject.getS().at(machineIndex).getTasks().size(); tryingT++) {
        intraMachineSwap(pmspObject.getS().at(machineIndex).getTasks(), current, tryingT);
        tmpZ = pmspObject.getZClassic();
        if (tmpZ < bestZ) {
          bestPmsp = pmspObject;
          bestZ = tmpZ;
          return true;
        }
        pmspObject = currentPmsp;
      }
    }
  }
  pmspObject = bestPmsp;
  return false;
}

void intraMachineInsertion(std::vector<Task>& tasks, int taskPos, int position) {
  if (position > tasks.size() - 1) {
    throw std::string("Posicion mayor que vector en IntraMachineInsertion\n");
  }
  if (taskPos == position) {
    return;
  }
  if (taskPos < position) {
    tasks.insert(tasks.begin() + position + 1, tasks[taskPos]);
    tasks.erase(tasks.begin() + taskPos);
  } else {
    tasks.insert(tasks.begin() + position, tasks[taskPos]);
    tasks.erase(tasks.begin() + taskPos + 1);
  }
}

void interMachineInsertion(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position) {
  if ((position > secondTasks.size()) || (taskPos > tasks.size() - 1 )) {
    throw std::string("Posicion mayor que vector en InterMachineInsertion\n");
  }
  secondTasks.insert(secondTasks.begin() + position, tasks[taskPos]);
  tasks.erase(tasks.begin() + taskPos);
}

void intraMachineSwap(std::vector<Task>& tasks, int taskPos, int position) {
  if ((taskPos > tasks.size() - 1) || (position > tasks.size() - 1)) {
    throw std::string("Posicion o taskpos mayor que vector en intraMachineSwap\n");
  }
  std::iter_swap(tasks.begin() + taskPos, tasks.begin() + position);
}

void interMachineSwap(std::vector<Task>& tasksOrig, std::vector<Task>& tasksDest, int taskPos, int position) {
  if (position > tasksDest.size() - 1) {
    throw std::string("Posicion mayor que vector en InterMachineInsertion\n");
  }
  std::iter_swap(tasksOrig.begin() + taskPos, tasksDest.begin() + position);
}