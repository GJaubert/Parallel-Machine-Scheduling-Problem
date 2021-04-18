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
  pmspObject.printSolution(1);
  greedyImprovement(pmspObject);
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
              //std::cout << "trying " << t[k].getId() << " in " << j << "\n";
            //std::cout << " predict: " << machines[i].predictTct(t[k], j, setup);
            tmpTct = machines[i].predictTct(t[k], j, setup);
            //machines[i].getTasks().insert(machines[i].getTasks().begin() + j, t[k]);
            //tmpTct = machines[i].getTctClassic(setup);
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

void Grasp::greedyImprovement(Pmsp pmspObject) {
  interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, 1);
  for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n";
  for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n\n";
  interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, 2);
  for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n";
  for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n\n";
  interMachineSwap(pmspObject.getS().at(0).getTasks(), pmspObject.getS().at(1).getTasks(), 0, pmspObject.getS().at(1).getTasks().size() - 1);
  for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n";
  for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n\n";
  interMachineSwap(pmspObject.getS().at(1).getTasks(), pmspObject.getS().at(0).getTasks(),3, 0);
  for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n";
  for (int i = 0; i < pmspObject.getS().at(1).getTasks().size(); i++) {
    std::cout << pmspObject.getS().at(1).getTasks().at(i).getId() << " ";
  }
  std::cout << "\n\n";

  // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, 1);
  // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
  //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  // }
  // std::cout << "\n\n";
  // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, 2);
  // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
  //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  // }
  // std::cout << "\n\n";
  // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 0, pmspObject.getS().at(0).getTasks().size() - 1);
  // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
  //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  // }
  // std::cout << "\n\n";
  // intraMachineSwap(pmspObject.getS().at(0).getTasks(), 3, 0);
  // for (int i = 0; i < pmspObject.getS().at(0).getTasks().size(); i++) {
  //   std::cout << pmspObject.getS().at(0).getTasks().at(i).getId() << " ";
  // }
  // std::cout << "\n\n";
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
  if (position > secondTasks.size()) {
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