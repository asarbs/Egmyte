//
// Created by asar on 09.07.16.
//

#ifndef EGNYTE_TIMERV0_HPP
#define EGNYTE_TIMERV0_HPP

#include <iostream>
#include <chrono>
#include <thread>


class TimerV0
{
public:
  TimerV0(void (*fun)(), std::chrono::milliseconds d, bool reRun = false) : _fun(fun), _duration(d),
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

  TimerV0( const TimerV0& ) = delete;

  ~TimerV0()
  { }


private:

  void (*_fun)();
  const std::chrono::milliseconds _duration;
  bool _run;
  bool _reRun;
  bool _error;
};


#endif //EGNYTE_TIMERV0_HPP
