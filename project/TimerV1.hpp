//
// Created by asar on 07.07.16.
//

#ifndef EGNYTE_TIMER_HPP
#define EGNYTE_TIMER_HPP

#include <iostream>
#include <functional>
#include <chrono>
#include <thread>

class TimerV1
{
public:
  TimerV1(std::function<void()>& fun, std::chrono::milliseconds d, bool reRun = false) : _fun(fun), _duration(d),
                                                                                       _run(true), _reRun(reRun),
                                                                                       _error(false)
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
                    if (!_fun)
                    {
                      _error = true;
                      return;
                    }
                    _fun();
                  } while (_reRun);

                }).detach();;
  }

  void stop()
  {
    _run = false;
  }

  bool isValid()
  {
    return  _error;
  }

  TimerV1( const TimerV1& ) = delete;

  ~TimerV1()
  { }


private:

  std::function<void()>& _fun;
  const std::chrono::milliseconds _duration;
  bool _run;
  bool _reRun;
  bool _error;
};


#endif //EGNYTE_TIMER_HPP
