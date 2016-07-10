//
// Created by asar on 21.06.16.
//

#include <gtest/gtest.h>
#include <Timer.hpp>

void foo(int x, int* out)
{
  *out = x * x;
}

void goo(int x, int* out)
{
  int tmp = *out;
  *out = tmp * x;
  //std::cerr << "p=" << out << " *out=" << (*out) << "=" << "(*out)=" << tmp << "* x=" << x << std::endl;
}

TEST(TimerV2, runSimpleTimer)
{
  std::chrono::milliseconds m(5);
  Timer<std::function<void (int, int*)>, int, int*> timerV2(&foo, m);
  int result = 155;
  timerV2.start(5, &result);
  while (!timerV2.isFinished())
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }

  EXPECT_EQ(25, result) ;
}

TEST(TimerV2, stopTimer)
{
  std::chrono::milliseconds m(15);

  Timer<std::function<void (int, int*)>, int, int*> t(&foo, m);
  int result = 10;
  t.start(5, &result);
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  t.stop();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(15));
  EXPECT_EQ(10, result);
}

TEST(TimerV2, reRunTimer)
{
  std::chrono::seconds m(2);
  Timer<std::function<void (int, int*)>, int, int*> t(&goo, m, true);
  int result = 10;
  t.start(5, &result);
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::seconds(5));
  EXPECT_EQ(250, result);
  std::this_thread::sleep_for(std::chrono::seconds(6));
  EXPECT_EQ(31250, result);
}

TEST(TimerV2, stopReRunTimer)
{
  std::chrono::seconds m(2);
  Timer<std::function<void (int, int*)>, int, int*> t(&goo, m, true);
  int result1 = 10;
  t.start(5, &result1);
  EXPECT_EQ(10, result1);
  std::this_thread::sleep_for(std::chrono::seconds(3));
  EXPECT_EQ(250, result1);
  t.stop();
  std::this_thread::sleep_for(std::chrono::seconds(6));
  EXPECT_EQ(250, result1);
}

void startTimer(int &outPut)
{
  std::chrono::seconds m(2);
  Timer<std::function<void (int, int*)>, int, int*> t(&goo, m);
  t.start(5, &outPut);
}

TEST(TimerV2, startInSeparateFunction)
{
  int result = 10;
  startTimer(result);
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::seconds(4));
  EXPECT_EQ(50, result);
}

