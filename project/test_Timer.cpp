//
// Created by asar on 21.06.16.
//

#include <gtest/gtest.h>
#include <Timer.hpp>


TEST(Timer, runSimpleTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(5);
  Timer t(f_foo, m);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(15, x);
}

TEST(Timer, stopTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  Timer t(f_foo, m);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  t.stop();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(15));
  EXPECT_EQ(10, x);
}

TEST(Timer, reRunTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  Timer t(f_foo, m, true);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(15, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(52));
  EXPECT_EQ(30, x);
}

TEST(Timer, stopReRunTimer)
{
  int x = 10;
  std::function<void()> f_foo = [&x]() -> void
  { x += 5; };
  std::chrono::milliseconds m(15);
  Timer t(f_foo, m, true);
  t.start();
  EXPECT_EQ(10, x);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(20, x);
  t.stop();
  EXPECT_EQ(20, x);
}
