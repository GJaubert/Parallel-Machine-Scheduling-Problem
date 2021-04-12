#include "../include/mygreedy.h"

std::vector<Machine> MyGreedy::computePmspSolution(Pmsp pmspObject){
  int minTask = 0, minMachine = 0;
  int lastItem = -1;
  for (int i = 0; i < pmspObject.getM(); i++) {
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), 0);  //obtener min de todas las tareas
    pmspObject.getTasks().at(minTask).setTctTime(pmspObject.getSetupTime().at(0).at(minTask + 1), 0);
    pmspObject.getS().at(i).getTasks().push_back(pmspObject.getTasks().at(minTask)); //pushear la minima tarea a la i maquina
    pmspObject.getS().at(i).updateTct(pmspObject.getTasks().at(minTask).getTaskTct()); //actualizar TCT de la maquina
  }
  int i = 0;
  int setupTime = 0;
  while (!pmspObject.allVisited()) {
    minMachine = getMinMachine(pmspObject.getS());
    lastItem = pmspObject.getS().at(minMachine).getTasks().size() - 1;
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS().at(minMachine).getTasks().at(lastItem).getId());
    setupTime = pmspObject.getSetupTime().at(pmspObject.getS().at(minMachine).getTasks().at(lastItem).getId()).at(minTask + 1);
    pmspObject.getTasks().at(minTask).setTctTime(setupTime, pmspObject.getS().at(minMachine).getTasks().at(lastItem).getTaskTct());
    pmspObject.getS().at(minMachine).getTasks().push_back(pmspObject.getTasks().at(minTask));
  }
  return pmspObject.getS();
}

int MyGreedy::getMinTask(std::vector<Task>& t, table setup, int originTask) {
  int min = 9999;
  int index = -1;
  for (int i = 0; i < t.size(); i++) {
    if ((t[i].getProcessTime() + setup[originTask][i + 1] < min) && (!t[i].getVisited())) {
      min = t[i].getProcessTime() + setup[originTask][i + 1];
      index = i;
    }
  }
  t[index].setVisited(true);
  return index;
}

int MyGreedy::getMinMachine(std::vector<Machine> m) {
  int min = 9999;
  int index = -1;
  for (int i = 0; i < m.size(); i++) {
    if (m[i].getTct() < min) {
      min = m[i].getTct();
      index = i;
    } 
  }
  return index;
}