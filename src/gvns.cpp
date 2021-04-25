#include "../include/gvns.h"
// grasp con intermaquinaswap

Pmsp Gvns::computePmspSolution(Pmsp pmspObject) {
  pmspObject = getGraspSolution(pmspObject);
  std::cout << "Grasp: \n";
  pmspObject.printSolution(1,0);
  pmspObject = Shake(pmspObject);
  return pmspObject;
}

Pmsp Gvns::Shake(Pmsp pmspObject) {
  for (int i = 0; i < 2; i++) {
    int machineIndex = rand() % pmspObject.getS().size();
    int destinyMachineIndex = rand() % pmspObject.getS().size();
    while (destinyMachineIndex == machineIndex) {
      destinyMachineIndex = rand() % pmspObject.getS().size();
    }
    int originTask = rand() % pmspObject.getS().at(machineIndex).getTasks().size();
    int destinyTask = rand() % pmspObject.getS().at(destinyMachineIndex).getTasks().size();
    interMachineSwap(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(destinyMachineIndex).getTasks(), originTask, destinyTask);
  }
  pmspObject.printSolution(1,0);
  return pmspObject;
}

// Pmsp Gvns::Vnd(Pmsp pmspObject) {

// }

void Gvns::interMachineSwap(std::vector<Task>& tasksOrig, std::vector<Task>& tasksDest, int taskPos, int position) {
  if (position > tasksDest.size() - 1) {
    throw std::string("Posicion mayor que vector en InterMachineInsertion\n");
  }
  std::iter_swap(tasksOrig.begin() + taskPos, tasksDest.begin() + position);
}

Pmsp Gvns::getGraspSolution(Pmsp pmspObject) {
  srand(time(NULL));
  std::shared_ptr<Grasp> graspStrat = std::make_shared<Grasp>();
  int tmpZ = 0;
  int notImprovementCounter = 0;
  Pmsp tmp(pmspObject);
  Pmsp best(pmspObject);
  best = graspStrat->getLocalOptimal(pmspObject, 2);
  int bestZ = best.getZ();
  while (notImprovementCounter < IMPROVEMENT_LIMIT) {
    tmp = graspStrat->getLocalOptimal(pmspObject, 2);
    tmpZ = tmp.getZ();
    if (tmp.getZ() < bestZ) {
      best = tmp;
      bestZ = tmpZ;
    } else {
      notImprovementCounter++;
    }
  }
  return best;
}