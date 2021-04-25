#include "../include/mygreedy.h"
using namespace std::chrono;

Pmsp MyGreedy::computePmspSolution(Pmsp pmspObject) {
  std::cout << "MyGreedy algorithm:\n\n";
  int minTask = 0, minMachine = 0;
  int lastItem = -1;
  auto start = high_resolution_clock::now();
  for (int i = 0; i < pmspObject.getM(); i++) {
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), 0);  //obtener min de todas las tareas
    pmspObject.getS().at(i).getTasks().push_back(pmspObject.getTasks().at(minTask)); //pushear la minima tarea a la i maquina
  }
  int i = 0;
  int setupTime = 0;
  while (!pmspObject.allVisited()) {
    minMachine = getMinMachine(pmspObject.getS(), pmspObject.getSetupTime());
    lastItem = pmspObject.getS().at(minMachine).getTasks().size() - 1;
    minTask = getMinTask(pmspObject.getTasks(), pmspObject.getSetupTime(), pmspObject.getS().at(minMachine).getTasks().at(lastItem).getId());
    pmspObject.getS().at(minMachine).getTasks().push_back(pmspObject.getTasks().at(minTask));
  }
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  pmspObject.printSolution(1, duration.count());
  return pmspObject;
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

int MyGreedy::getMinMachine(std::vector<Machine> m, table setup) {
  int min = 9999;
  int index = -1;
  for (int i = 0; i < m.size(); i++) {
    if (m[i].getTctClassic(setup) < min) {
      min = m[i].getTctClassic(setup);
      index = i;
    } 
  }
  return index;
}