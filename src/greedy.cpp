#include "../include/greedy.h"
using namespace std::chrono;

Pmsp Greedy::computePmspSolution(Pmsp pmspObject) {
  std::cout << "Classic Greedy:\n\n";
  int minTask = BIG_NUMBER;
  int minTaskIndex = -1;
  int tmpTask = 0;
  int tmpTaskValue = 0;
  auto start = high_resolution_clock::now();
  for (int i = 0; i < pmspObject.getM(); i++) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS());  //obtener min de todas las tareas
  }
  while (!pmspObject.allVisited()) {
    getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS());
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  pmspObject.printSolution(1, duration.count());
  return pmspObject;
}

void Greedy::getMinTask(std::vector<Task>& t, table setup, std::vector<Machine>& machines) {
  int min = BIG_NUMBER;
  int indexI = -1;
  int indexJ = -1;
  int indexK = -1;
  int tmpTct = 0;
  int originalTct = 0;
  for (int i = 0; i < machines.size(); i++) { // maquina que usas
    originalTct = machines[i].getTctClassic(setup);
    for (int j = 0; j <= machines[i].getTasks().size(); j++) { //tarea desde la que sale la siguiente
      for (int k = 0; k < t.size(); k++) { // tarea de prueba a ver si es minimo 
        if (t[k].getVisited())
          continue;
        if (machines[i].getTasks().size() == 0) {
          machines[i].getTasks().push_back(t[k]);
        }
        else if (j <= machines[i].getTasks().size()){
          machines[i].getTasks().insert(machines[i].getTasks().begin() + j, t[k]);
        }
        tmpTct = machines[i].getTctClassic(setup);
        if (((tmpTct - originalTct) < min)) {
          min = tmpTct - originalTct;
          indexI = i;
          indexJ = j;
          indexK = k;
        }
        machines[i].getTasks().erase(machines[i].getTasks().begin() + j);
      }
    }
  }
  if (machines[indexI].getTasks().size() == 0) {
    machines[indexI].getTasks().push_back(t[indexK]);
  }
  else {
    machines[indexI].getTasks().insert(machines[indexI].getTasks().begin() + indexJ, t[indexK]);
  }
  t[indexK].setVisited(true);
}