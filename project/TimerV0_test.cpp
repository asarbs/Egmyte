//
// Created by asar on 21.06.16.
//

#include <gtest/gtest.h>

#include <mutex>

#include <TimerV0.hpp>

std::mutex mutex;
static int result = 10;

void foo()
{
  mutex.lock();
  result += 5;
  mutex.unlock();
}

class TestTimerV0: public testing::Test
{
protected:
  virtual void SetUp()
  {
    result = 10;
  }
  virtual void TearDown()
  {}
};


TEST_F(TestTimerV0, runSimpleTimer)
{
  std::chrono::milliseconds m(5);
  TimerV0 t(foo , m);
  t.start();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  EXPECT_EQ(15, result);
}

TEST_F(TestTimerV0, stopTimer)
{
  std::chrono::milliseconds m(15);
  TimerV0 t(foo, m);
  t.start();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  t.stop();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(15));
  EXPECT_EQ(10, result);
}

TEST_F(TestTimerV0, reRunTimer)
{
  std::chrono::milliseconds m(15);
  TimerV0 t(foo, m, true);
  t.start();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(15, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(52));
  EXPECT_EQ(30, result);
}

TEST_F(TestTimerV0, stopReRunTimer)
{
  std::chrono::milliseconds m(15);
  TimerV0 t(foo, m, true);
  t.start();
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(20, result);
  t.stop();
  EXPECT_EQ(20, result);
}

void startTimer(int& outParam)
{
  std::chrono::milliseconds m(5);
  TimerV0 t(foo, m);
  t.start();
}

TEST_F(TestTimerV0, startInSeparateFunction)
{
  startTimer(result);
  EXPECT_EQ(10, result);
  std::this_thread::sleep_for(std::chrono::milliseconds(22));
  EXPECT_EQ(15, result);
}
