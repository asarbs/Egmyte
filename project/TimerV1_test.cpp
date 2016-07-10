//
// Created by asar on 21.06.16.
//

#include <gtest/gtest.h>
#include <TimerV1.hpp>

TEST(TimerV1, runSimpleTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(5);
  TimerV1 t(f_foo, m);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(15, x);
}

TEST(TimerV1, stopTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  TimerV1 t(f_foo, m);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  t.stop();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(15));
  EXPECT_EQ(10, x);
}

TEST(TimerV1, reRunTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  TimerV1 t(f_foo, m, true);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(15, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(52));
  EXPECT_EQ(30, x);
}

TEST(TimerV1, stopReRunTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  TimerV1 t(f_foo, m, true);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(20, x);
  t.stop();
  EXPECT_EQ(20, x);
}


void startTimer1(int& outParam)
{
  std::function<void()> f_foo = [&outParam]() -> void
  {
    outParam += 5;
  };
  std::chrono::milliseconds m(5);
  TimerV1 t(f_foo, m);
  t.start();
}

TEST(TimerV1, startInSeparateFunction)
{
  int result = 10;
  startTimer1(result);
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::seconds(2));
  EXPECT_EQ(15, result);
}

