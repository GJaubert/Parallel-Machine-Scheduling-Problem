#include "../include/greedy.h"

std::vector<Machine> Greedy::computePmspSolution(Pmsp pmspObject){
  int minTask = 9999;
  int minTaskIndex = -1;
  int tmpTask = 0;
  int tmpTaskValue = 0;
  for (int i = 0; i < pmspObject.getM(); i++) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS());  //obtener min de todas las tareas
  }
  while (!pmspObject.allVisited()) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS());
  }
  return pmspObject.getS();
}

void Greedy::getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machines) {
  int min = 9999;
  int indexI = -1;
  int indexJ = -1;
  int indexK = -1;
  int tmpTct = 0;
  int originalTct = 0;
  int incremento = 0;
  for (int i = 0; i < machines.size(); i++) { // maquina que usas
    originalTct = machines[i].getTctClassic(setup);
    for (int j = 0; j <= machines[i].getTasks().size(); j++) { //tarea desde la que sale la siguiente
      for (int k = 0; k < t.size(); k++) { // tarea de prueba a ver si es minimo 
        if ((j == machines[i].getTasks().size()) && (j > 0))
          continue;
        if (machines[i].getTasks().size() == 0) {
          machines[i].getTasks().push_back(t[k]);
        }
        else {
          t[k].setSetupTime(setup[machines[i].getTasks().at(j).getId()][k + 1]);
          machines[i].getTasks().insert(machines[i].getTasks().begin() + j + 1, t[k]);
        }
        tmpTct = machines[i].getTctClassic(setup);
        if (((tmpTct - originalTct) < min) && (!t[k].getVisited())) {
          min = tmpTct - originalTct;
          indexI = i;
          indexJ = j;
          indexK = k;
        }
        machines[i].getTasks().erase(machines[i].getTasks().begin() + j + 1);
      }
    }
  }
  if (machines[indexI].getTasks().size() == 0) {
    machines[indexI].getTasks().push_back(t[indexK]);
  }
  else {
    machines[indexI].getTasks().insert(machines[indexI].getTasks().begin() + indexJ + 1, t[indexK]);
  }
  t[indexK].setVisited(true);
}