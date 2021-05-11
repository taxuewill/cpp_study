#include <vector>
#include <iostream>
#include <thread>
#include <atomic>
#include <string>

std::atomic<int> cnt = {0};
using namespace std;
void f()
{
  for (int n = 0; n < 1000; ++n)
  {
    cnt.fetch_add(1, std::memory_order_relaxed);
  }
}

int main()
{
  //  const char* s1 = "hello";
  string s1("hello");
  string s2("hello");
  if (s1 == s2)
  {
    cout << "equals" << endl;
  }
  cout << s1 << endl;
}