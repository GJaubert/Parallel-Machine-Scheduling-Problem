#include "../include/greedy.h"

std::vector<Machine> Greedy::computePmspSolution(Pmsp pmspObject){
  int minTask = 9999;
  int minTaskIndex = -1;
  int tmpTask = 0;
  int tmpTaskValue = 0;
  for (int i = 0; i < pmspObject.getM(); i++) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), minTask, pmspObject.getS());  //obtener min de todas las tareas
  }
  getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), minTask, pmspObject.getS());
  //getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), minTask, pmspObject.getS());
   int i = 0;
  while (!pmspObject.allVisited()) {
  //while (i < 6) {
  getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), minTask, pmspObject.getS());
  //   getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), tmpTaskValue, pmspObject.getS());
  i++;
  }
    //std::cout << "mtct: " << pmspObject.getS().at(minMachine).getTct() << " \n"; // .getTasks().at(minTask - 1).getTaskTct();
  return pmspObject.getS();
}

int Greedy::getMinTask(std::vector<Task>& t, table setup, int& tmpTaskValue, std::vector<Machine>& machines) {
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
        //originalTct = machines[i].getTctClassic(setup);
        //std::cout << "sizeprimero " <<  machines[i].getTasks().size() << "\n";
        if (machines[i].getTasks().size() == 0) {
          //std::cout << "pas";
          machines[i].getTasks().push_back(t[k]);
        }
        else {
          //machines[i].getTasks().resize(machines[i].getTasks().size() + 1);
          //std::cout << "setup " << setup[machines[i].getTasks().at(j).getId()][k + 1] << " origen: " << machines[i].getTasks().at(j).getId() << "\n";
          t[k].setSetupTime(setup[machines[i].getTasks().at(j).getId()][k + 1]);
          machines[i].getTasks().insert(machines[i].getTasks().begin() + j + 1, t[k]);
        }
        // for(int l = 0; l < machines[i].getTasks().size(); l++)
        //std::cout << t[i].getId();
        // if (k + 1 == 5)
        //std::cout << "task" << k + 1 << " from " << machines[i].getTasks().at(j).getId() <<"\n";
        tmpTct = machines[i].getTctClassic(setup);
        //std::cout << "tct: " << tmpTct  << " i: " << i << " j: " << j << " k: " << k << "\n";
        if (((tmpTct - originalTct) < min) && (!t[k].getVisited())) {
          //std::cout << "task" << k + 1 << " tct: "<< tmpTct << " min " << min <<  "\n";
          min = tmpTct - originalTct;
          indexI = i;
          indexJ = j;
          indexK = k;
        }
        machines[i].getTasks().erase(machines[i].getTasks().begin() + j + 1);
      }
    }
  }
  //std::cout << "size segundo " <<machines[indexI].getTasks().size() << "\n";
  if (machines[indexI].getTasks().size() == 0) {
    machines[indexI].getTasks().push_back(t[indexK]);
  }
  else {
   // std::cout << "inserted task: " << indexK + 1 << " on position: " << indexJ + 1 << " machine: " << indexI << "\n";
    machines[indexI].getTasks().insert(machines[indexI].getTasks().begin() + indexJ + 1, t[indexK]);
  }
  //std::cout << setup[machines[indexI].getTasks().at(indexJ).getId()][indexK + 1];
  //machines[indexI].getTasks().at(indexJ).setSetupTime(setup[machines[indexI].getTasks().at(indexJ).getId()][indexK + 1]);
  t[indexK].setVisited(true);
  return indexI;
}