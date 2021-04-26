#include "../include/gvns.h"
using namespace std::chrono;
// grasp con intermaquinaswap

Pmsp Gvns::computePmspSolution(Pmsp pmspObject) {
  int k = 0;
  int nIter = 0;
  int bestZ = pmspObject.getZ();
  int tmpZ = 0;
  int bestZGlobal = BIG_NUMER;
  int tmpZGlobal = 0;
  Pmsp environmentObject(pmspObject);
  Pmsp bestZObject(pmspObject);
  Pmsp bestZGlobalObject(pmspObject);
  std::cout << "Gvns:\n\n";
  auto start = high_resolution_clock::now();
  if (STOP_CONDITION == 0) {
    do {
      k = 0;
      Pmsp graspObject(getGraspSolution(pmspObject));
      tmpZ = 0;
      bestZ = graspObject.getZ();
      do {
        environmentObject = graspObject;
        environmentObject = Vnd(Shake(environmentObject));
        tmpZ = environmentObject.getZ();
        if (tmpZ < bestZ) {
          bestZObject = environmentObject;
          bestZ = tmpZ;
        }
        k++;
      } while (k < KMAX);
      tmpZGlobal = bestZObject.getZ();
      if (tmpZGlobal < bestZGlobal) {
        bestZGlobal = tmpZGlobal;
        bestZGlobalObject = bestZObject;
      }
      //std::cout << nIter << "\n";
      nIter++;
    } while (nIter < N_ITER_MAX);
  }
  if (STOP_CONDITION == 1) {
    std::cout << "improvement";
    int noImprovementCounter = 0;
    do {
      k = 0;
      Pmsp graspObject(getGraspSolution(pmspObject));
      tmpZ = 0;
      bestZ = graspObject.getZ();
      do {
        environmentObject = graspObject;
        environmentObject = Vnd(Shake(environmentObject));
        tmpZ = environmentObject.getZ();
        if (tmpZ < bestZ) {
          bestZObject = environmentObject;
          bestZ = tmpZ;
        }
        k++;
      } while (k < KMAX);
      tmpZGlobal = bestZObject.getZ();
      if (tmpZGlobal < bestZGlobal) {
        bestZGlobal = tmpZGlobal;
        bestZGlobalObject = bestZObject;
        noImprovementCounter = 0;
      } else {
        noImprovementCounter++;
      }
    } while (noImprovementCounter < NO_IMPROVEMENT);
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  bestZGlobalObject.printSolution(1, duration.count());
  return bestZGlobalObject;
}

Pmsp Gvns::Shake(Pmsp pmspObject) {
  for (int i = 0; i < 2; i++) {
    int machineIndex = rand() % pmspObject.getS().size();
    int destinyMachineIndex = (machineIndex < pmspObject.getS().size() - 1) ? machineIndex++ : machineIndex--;
    int originTask = rand() % pmspObject.getS().at(machineIndex).getTasks().size();
    int destinyTask = rand() % pmspObject.getS().at(destinyMachineIndex).getTasks().size();
    interMachineInsertion(pmspObject.getS().at(machineIndex).getTasks(), pmspObject.getS().at(destinyMachineIndex).getTasks(), originTask, destinyTask);
  }
  return pmspObject;
}

Pmsp Gvns::Vnd(Pmsp pmspObject) {
  bool improvement = false;
  Pmsp pmspObjectOriginal(pmspObject);
  if (VND_MOVEMENTS_SET == 0) {
    do {
      for (int i = 0; i < MOVEMENT_TYPES / 2; i++) {
        pmspObject = pmspObjectOriginal;
        improvement = selectMovement(pmspObject, i);
        if (improvement) {
          pmspObjectOriginal = pmspObject;
          break;
        }
      }
    } while (improvement);
  }
  if (VND_MOVEMENTS_SET == 1) {
    do {
      for (int i = 4; i < MOVEMENT_TYPES; i++) {
        pmspObject = pmspObjectOriginal;
        improvement = selectMovement(pmspObject, i);
        if (improvement) {
          pmspObjectOriginal = pmspObject;
          break;
        }
      }
    } while (improvement);
  }
  return pmspObject;
}

bool Gvns::selectMovement(Pmsp& pmspObject, int type) {
  bool improvement = false;
  switch (type) {
    case 0:
      improvement = greedyImprovementIntraMachineSwap(pmspObject);
      break;
    case 1:
      improvement = greedyImprovementIntraMachineInsert(pmspObject);
      break;
    case 2:
      improvement = greedyImprovementInterMachineSwap(pmspObject);
      break;
    case 3:
      improvement = greedyImprovementInterMachineInsert(pmspObject);
      break;
    case 4:
      improvement = lazyImprovementInterMachineInsert(pmspObject);
      break;
    case 5:
      improvement = lazyImprovementIntraMachineInsert(pmspObject);
      break;
    case 6:
      improvement = lazyImprovementInterMachineSwap(pmspObject);
      break;
    case 7:
      improvement = lazyImprovementIntraMachineSwap(pmspObject);
      break;
    default:
      throw std::string("GetLocalOptimal: No type found\n");
      break;
  }
  return improvement;
}

Pmsp Gvns::getGraspSolution(Pmsp pmspObject) {
  srand(time(NULL));
  std::shared_ptr<Grasp> graspStrat = std::make_shared<Grasp>();
  int tmpZ = 0;
  int noImprovementCounter = 0;
  Pmsp tmp(pmspObject);
  Pmsp best(pmspObject);
  best = graspStrat->getLocalOptimal(pmspObject, 0);
  int bestZ = best.getZ();
  for (int i = 1; i < ITERATIONS_LIMIT; i++) {
    tmp = graspStrat->getLocalOptimal(pmspObject, 0);
    tmpZ = tmp.getZ();
    if (tmp.getZ() < bestZ) {
      best = tmp;
      bestZ = tmpZ;
    }
  }
  return best;
}