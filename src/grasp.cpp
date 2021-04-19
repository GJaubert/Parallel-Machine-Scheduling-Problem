#include "../include/grasp.h"
using namespace std::chrono;

struct KElement {
  int i_;
  int j_;
  int k_;
};

std::vector<Machine> Grasp::computePmspSolution(Pmsp pmspObject){
  srand (time(NULL));
  std::cout << "Grasp construction phase: " << "\n";
  Pmsp constructionObject(pmspObject);
  auto start = high_resolution_clock::now();
  construction(constructionObject);
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  constructionObject.printSolution(1, duration.count());
  std::cout << "Stop condition: fixed iterations\n";
  for (int type = 0; type < MOVEMENT_TYPES; type++) {
    printTitle(type);
    int tmpZ = 0;
    Pmsp tmp(pmspObject);
    Pmsp best(pmspObject);
    auto start = high_resolution_clock::now();
    best = getLocalOptimal(pmspObject, type);
    int bestZ = best.getZ();
    for (int iteration = 1; iteration < ITERATIONS_LIMIT; iteration++) {
      tmp = getLocalOptimal(pmspObject, type);
      tmpZ = tmp.getZ();
      if (tmp.getZ() < bestZ) {
        best = tmp;
        bestZ = tmpZ;
      }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    best.printSolution(1, duration.count());
  }
  std::cout << "-----------------------------------------";
  std::cout << "Stop condition: no improve\n";
  for (int type = 0; type < MOVEMENT_TYPES; type++) {
    printTitle(type);
    int tmpZ = 0;
    int notImprovementCounter = 0;
    Pmsp tmp(pmspObject);
    Pmsp best(pmspObject);
    auto start = high_resolution_clock::now();
    best = getLocalOptimal(pmspObject, type);
    int bestZ = best.getZ();
    while (notImprovementCounter < IMPROVEMENT_LIMIT) {
      tmp = getLocalOptimal(pmspObject, type);
      tmpZ = tmp.getZ();
      if (tmp.getZ() < bestZ) {
        best = tmp;
        bestZ = tmpZ;
      } else {
        notImprovementCounter++;
      }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    best.printSolution(1, duration.count());
  }
  return pmspObject.getS();
}

void Grasp::construction(Pmsp& pmspObject) {
  for (int i = 0; i < pmspObject.getM(); i++) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS(), pmspObject.getK());
  }
  while (!pmspObject.allVisited()) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS(), pmspObject.getK());
  }
}

Pmsp Grasp::getLocalOptimal(Pmsp pmspObject, int type) {
  construction(pmspObject);
  bool improvement = false;
  do {
    switch (type) {
    case 0:
      improvement = greedyImprovementInterMachineInsert(pmspObject);
      break;
    case 1:
      improvement = greedyImprovementIntraMachineInsert(pmspObject);
      break;
    case 2:
      improvement = greedyImprovementInterMachineSwap(pmspObject);
      break;
    case 3:
      improvement = greedyImprovementIntraMachineSwap(pmspObject);
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
  } while (improvement);
  return pmspObject;
}

void Grasp::getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machines, int kGrasp) {
  int min = BIG_NUMBER;
  int tmpTct = 0;
  int RandomIndex = 0;
  int originalTct = 0;
  std::vector<KElement> bestK;
  for (int l = 0; l < kGrasp; l++) {
    KElement newk;
    for (int i = 0; i < machines.size(); i++) { // maquina que usas
      originalTct = machines[i].getTctClassic(setup);
      if (machines[i].getTasks().size() == 0) {
        initialCase(t, setup, machines[i], newk, i);  //Inicializacion
        break;
      } else {
        for (int j = 0; j <= machines[i].getTasks().size(); j++) { //tarea desde la que sale la siguiente
          for (int k = 0; k < t.size(); k++) { // tarea de prueba a ver si es minimo 
            if (t[k].getVisited())
              continue;
            tmpTct = machines[i].predictTct(t[k], j, setup);
            if (((tmpTct - originalTct) < min)) {
              min = tmpTct - originalTct;
              newk.i_ = i;
              newk.j_ = j;
              newk.k_ = k;
            }
          }
        }
      }
    }
    t[newk.k_].setVisited(true);
    min = BIG_NUMBER;
    bestK.push_back(newk);
  }
  insertRandom(t, machines, bestK);
}

void Grasp::initialCase(std::vector<Task>& t, table setup, Machine& machine, KElement& newk, int machineIndex) {
  int min = BIG_NUMBER;
  for (int k = 0; k < t.size(); k++) {
    if (t[k].getVisited())
      continue;
    machine.getTasks().push_back(t[k]);
    int tmpTct = machine.getTctClassic(setup);
    if (tmpTct < min) {
      min = tmpTct;
      newk.i_ = machineIndex;
      newk.k_ = k;
    }
    machine.getTasks().pop_back();
  }
}

void Grasp::insertRandom(std::vector<Task>& t, std::vector<Machine>& machines, std::vector<KElement>& bestK) {
  int RandomIndex = rand() % bestK.size();
  if (machines[bestK[RandomIndex].i_].getTasks().size() == 0) {
    machines[bestK[RandomIndex].i_].getTasks().push_back(t[bestK[RandomIndex].k_]);
  }
  else {
    machines[bestK[RandomIndex].i_].getTasks().insert(machines[bestK[RandomIndex].i_].getTasks().begin() + bestK[RandomIndex].j_, t[bestK[RandomIndex].k_]);
  }
  for(int i = 0; i < bestK.size(); i++) {
    t[bestK[i].k_].setVisited(false);
  }
  t[bestK[RandomIndex].k_].setVisited(true);
}

bool Grasp::greedyImprovementInterMachineInsert(Pmsp& pmspObject) {
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

bool Grasp::greedyImprovementInterMachineSwap(Pmsp& pmspObject) {
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

bool Grasp::greedyImprovementIntraMachineInsert(Pmsp& pmspObject) {
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

bool Grasp::greedyImprovementIntraMachineSwap(Pmsp& pmspObject) {
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

bool Grasp::lazyImprovementInterMachineInsert(Pmsp& pmspObject) {
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

bool Grasp::lazyImprovementIntraMachineInsert(Pmsp& pmspObject) {
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

bool Grasp::lazyImprovementInterMachineSwap(Pmsp& pmspObject) {
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

bool Grasp::lazyImprovementIntraMachineSwap(Pmsp& pmspObject) {
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

void Grasp::intraMachineInsertion(std::vector<Task>& tasks, int taskPos, int position) {
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

void Grasp::interMachineInsertion(std::vector<Task>& tasks, std::vector<Task>& secondTasks, int taskPos, int position) {
  if ((position > secondTasks.size()) || (taskPos > tasks.size() - 1 )) {
    throw std::string("Posicion mayor que vector en InterMachineInsertion\n");
  }
  secondTasks.insert(secondTasks.begin() + position, tasks[taskPos]);
  tasks.erase(tasks.begin() + taskPos);
}

void Grasp::intraMachineSwap(std::vector<Task>& tasks, int taskPos, int position) {
  if ((taskPos > tasks.size() - 1) || (position > tasks.size() - 1)) {
    throw std::string("Posicion o taskpos mayor que vector en intraMachineSwap\n");
  }
  std::iter_swap(tasks.begin() + taskPos, tasks.begin() + position);
}

void Grasp::interMachineSwap(std::vector<Task>& tasksOrig, std::vector<Task>& tasksDest, int taskPos, int position) {
  if (position > tasksDest.size() - 1) {
    throw std::string("Posicion mayor que vector en InterMachineInsertion\n");
  }
  std::iter_swap(tasksOrig.begin() + taskPos, tasksDest.begin() + position);
}

void Grasp::printTitle(int type) {
  switch(type) { 
    case 0:
      std::cout << "Greedy InterMachineInsert: " << "\n"; 
      break;
    case 1:
      std::cout << "Greedy IntraMachineInsert: " << "\n"; 
      break;
    case 2:
      std::cout << "Greedy InterMachineSwap: " << "\n"; 
      break;
    case 3:
      std::cout << "Greedy IntraMachineSwap: " << "\n";
      break;
    case 4:
      std::cout << "Lazy InterMachineInsert: " << "\n";
      break;
    case 5:
      std::cout << "Lazy IntraMachineInsert: " << "\n"; 
      break;
    case 6:
      std::cout << "Lazy InterMachineSwap: " << "\n"; 
      break;
    case 7:
      std::cout << "Lazy IntraMachineSwap: " << "\n";
      break;
    default:
      throw std::string("PrintTitle no case found\n");
      break;
  }
}

// void Grasp::greedyImprovementInterMachine(Pmsp pmspObject) {
//   interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, 1);
//   for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n";
//   for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n\n";
//   interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, 2);
//   for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n";
//   for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n\n";
//   interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, pmspObject.getS().at(1).getTasks().size() - 1);
//   for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n";
//   for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n\n";
//   interMachineSwap(pmspObject.getS().at(1).getTasks(), pmspObject.getS().at(0).getTasks(),3, 0);
//   for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n";
//   for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
//     std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
//   }
//   std::cout << "\n\n";

//   // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, 1);
//   // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//   //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   // }
//   // std::cout << "\n\n";
//   // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, 2);
//   // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//   //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   // }
//   // std::cout << "\n\n";
//   // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, pmspObject.getS().at(0).getTasks().size() - 1);
//   // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//   //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   // }
//   // std::cout << "\n\n";
//   // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 3, 0);
//   // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
//   //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
//   // }
//   // std::cout << "\n\n";
// }