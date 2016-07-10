//
// Created by asar on 10.07.16.
//

#ifndef EGNYTE_TIMERV2_HPP
#define EGNYTE_TIMERV2_HPP

#include <functional>
#include <chrono>
#include <future>
#include <iostream>

template <class callable, class... arguments>
class Timer
{
public:
  Timer(callable&& f, std::chrono::milliseconds d, bool reRun = false):_callable(f), _duration(d), _reRun(reRun), _done(false)
  {}

  void start(arguments&&... args)
  {

    std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(_callable), std::forward<arguments>(args)...));

    _t = std::thread([this, task]() -> void
                {
                  do
                  {
                    std::this_thread::sleep_for(_duration);
                    if (!_run)
                    {
                      return;
                    }
                    task();
                  } while (_reRun);
                  _done = true;
                });
    _t.detach();
  }

  void stop()
  {
    _run = false;
  }

  bool isFinished()
  {
    return _done;
  }


private:
  callable _callable;
  const std::chrono::milliseconds _duration;
  bool _run;
  bool _reRun;
  bool _done;
  std::thread _t;

};



#endif //EGNYTE_TIMERV2_HPP
