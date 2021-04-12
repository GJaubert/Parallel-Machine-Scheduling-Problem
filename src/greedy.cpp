#include "../include/greedy.h"

std::vector<Machine> Greedy::computePmspSolution(Pmsp pmspObject){
  int minTask = 0, minMachine = 0;
  int lastItem = -1;
  for (int i = 0; i < pmspObject.getM(); i++) {
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), 0);  //obtener min de todas las tareas
    pmspObject.getTasks().at(minTask).setTctTime(pmspObject.getSetupTime().at(0).at(minTask + 1), 0);
    pmspObject.getS().at(i).getTasks().push_back(pmspObject.getTasks().at(minTask)); //pushear la minima tarea a la i maquina
    pmspObject.getS().at(i).updateTct(pmspObject.getTasks().at(minTask).getTaskTct()); //actualizar TCT de la maquina
    // std::cout << "id: " << pmspObject.getTasks().at(minTask).getId() << " ";
    // std::cout << "pt: " << pmspObject.getTasks().at(minTask).getProcessTime() << " ";
    // std::cout << pmspObject.getS().at(i).getTct() << std::endl;
  }
  int i = 0;
  int setupTime = 0;
  while (!pmspObject.allVisited()) {
  // while (i < 3) {
    minMachine = getMinMachine(pmspObject.getS());
    lastItem = pmspObject.getS().at(minMachine).getTasks().size() - 1;
    //std::cout << pmspObject.getS().at(minMachine).getTasks().size() - 1;
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS().at(minMachine).getTasks().at(lastItem).getId());
    setupTime = pmspObject.getSetupTime().at(pmspObject.getS().at(minMachine).getTasks().at(lastItem).getId()).at(minTask + 1);
    pmspObject.getTasks().at(minTask).setTctTime(setupTime, pmspObject.getS().at(minMachine).getTasks().at(lastItem).getTaskTct());
    pmspObject.getS().at(minMachine).getTasks().push_back(pmspObject.getTasks().at(minTask));
    //std::cout << "id " << pmspObject.getS().at(minMachine).getTasks().at(lastItem + 1).getId() << " ";
    // std::cout << "m: " << minMachine << " ";
    // std::cout << "mtct: " << pmspObject.getS().at(minMachine).getTct() << " "; // .getTasks().at(minTask - 1).getTaskTct();
    // std::cout << "taskTct: " << pmspObject.getTasks().at(minTask).getTaskTct();
  }
  // std::cout << "\n"<<pmspObject.getS().at(0).getTct() << "\n";
  // std::cout << pmspObject.getS().at(1).getTct() << "\n";
  return pmspObject.getS();
}

int Greedy::getMinTask(std::vector<Task>& t, table setup, int originTask) {
  int min = 9999;
  int index = -1;
  for (int i = 0; i < t.size(); i++) {
    if ((t[i].getProcessTime() + setup[originTask][i + 1] < min) && (!t[i].getVisited())) {
      //std::cout << t[i].getProcessTime() + setup[originTask][i + 1] << " ";
      min = t[i].getProcessTime() + setup[originTask][i + 1];
      index = i;
    }
  }
  //std::cout << std::endl;
  //t[min].setTctTime(t[min].getProcessTime() + setup[originTask][min]);
  t[index].setVisited();
  return index;
}


int Greedy::getMinMachine(std::vector<Machine> m) {
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