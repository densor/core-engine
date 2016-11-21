#include "ICLLockingThreadManager.h"
#include "SetTask.h"
#include <iostream>

int main(void)
{
  nsCore::LockingThreadManager* threads = new nsCore::LockingThreadManager(7);

  const int size = 100000;
  int* values = new int[size];
  std::vector<nsCore::IThreadTask*> tasks;
  std::vector<unsigned> blocked;
  blocked.push_back(1);

  for(int i = 0; i < size; ++i)
  {
    values[i] = size + 1;
    tasks.push_back(new nsCore::nsTest::SetTaskInt(values + i, i, blocked));
  }
  
  threads->ScheduleTasks(tasks, nsCore::IThreadTaskScheduler::TE_SHORT_TASK);
  tasks.clear();

  threads->Synchonize(1);

  bool good = true;
  for(int i = 0; i < size; ++i)
  {
    good &= (values[i] == i);
  }

  if(good)
  {
    std::cout << "Test successful." << std::endl;
  }
  else
  {
    std::cout << "Test failed." << std::endl;
  }

  int in;
  std::cin >> in;
  
  delete [] values;
  delete threads;
}