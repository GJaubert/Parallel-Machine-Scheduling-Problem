#include "../include/grasp.h"

struct KElement {
  int i_;
  int j_;
  int k_;
};

std::vector<Machine> Grasp::computePmspSolution(Pmsp pmspObject){
  srand (time(NULL));
  for (int i = 0; i < pmspObject.getM(); i++) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS(), pmspObject.getK());
  }
  while (!pmspObject.allVisited()) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS(), pmspObject.getK());
  }
  return pmspObject.getS();
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
            machines[i].getTasks().insert(machines[i].getTasks().begin() + j, t[k]);
            tmpTct = machines[i].getTctClassic(setup);
            if (((tmpTct - originalTct) < min)) {
              min = tmpTct - originalTct;
              newk.i_ = i;
              newk.j_ = j;
              newk.k_ = k;
            }
            machines[i].getTasks().erase(machines[i].getTasks().begin() + j);
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