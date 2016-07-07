//
// Created by asar on 07.07.16.
//

#ifndef EGNYTE_TIMER_HPP
#define EGNYTE_TIMER_HPP

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include <iostream>

class Timer
{
public:
  Timer(std::function<void()> &fun, std::chrono::milliseconds d, bool reRun = false) : _fun(fun), _duration(d),
                                                                                       _run(true), _reRun(reRun)
  { }

  void start()
  {
    std::thread([this]() -> void
                {
                  do
                  {
                    std::chrono::milliseconds timeCounter(0);
                    while (timeCounter < _duration)
                    {
                      std::this_thread::sleep_for(std::chrono::milliseconds(1));
                      if (!_run)
                      {
                        return;
                      }
                      timeCounter++;
                    }
                    _fun();
                  } while (_reRun);

                }).detach();;
  }

  void stop()
  {
    _run = false;
  }

  ~Timer()
  { }

private:
  Timer() : _duration(0), _run(false), _reRun(false)
  { }

  std::function<void()> _fun;
  const std::chrono::milliseconds _duration;
  bool _run;
  bool _reRun;
};


#endif //EGNYTE_TIMER_HPP
