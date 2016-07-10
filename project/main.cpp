#include <iostream>

#include <Timer.hpp>

void foo(int x, int* out)
{
  *out = x * x;
}

int main()
{
  std::chrono::seconds m(5);
  Timer<std::function<void (int, int*)>, int, int*> timerV2(&foo, m);
  int result = 155;
  timerV2.start(5, &result);
  std::chrono::seconds m1(1);
  while (!timerV2.isFinished())
  {
    std::this_thread::sleep_for(m1);
  }
  return 25 == result;
}


