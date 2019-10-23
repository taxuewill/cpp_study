// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <unistd.h>
#include <vector>

using namespace std;
void foo() 
{
  // do stuff...
  cout<<"foo"<<endl;
}

void bar(int x)
{
  // do stuff...
  cout<<"bar"<<endl;
}

int main() 
{
//   std::thread first (foo);     // spawn new thread that calls foo()
//   std::thread second (bar,0);  // spawn new thread that calls bar(0)

//   std::cout << "main, foo and bar now execute concurrently...\n";
// usleep(1000*1000);
//   // synchronize threads:
//   first.join();                // pauses until first finishes
//   second.join();               // pauses until second finishes
  vector<int> testVec;
  testVec.push_back(1);
  // testVec[0] = 1;
  cout<<"...capacity "<<testVec.capacity()<<endl;

  std::cout << "foo and bar completed.\n";

  return 0;
}