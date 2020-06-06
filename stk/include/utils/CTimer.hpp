#ifndef C_TIMER_HPP
#define C_TIMER_HPP

#include <thread>
#include <functional>

namespace stk
{

using OnTimerFunc = std::function<void()>;

class CTimer
{

public:
    /*!
     * \param 
     * \param _cnt -1 : run all the time; 0 : not run;
     */
    CTimer(OnTimerFunc _func,
           int _interval = -1,
           int _cnt = -1,
           bool _auto_start = false);
    ~CTimer();

    void Start();
    void Stop();
    void Pause();

private:
    void createThread();
    void onRunning();
    void exit();

private:
    OnTimerFunc m_func;
    int  m_cnt;
    int  m_interval;
    bool m_inited;
    bool m_running;

    int  m_step;
    int  m_tick;

    std::thread m_thread;
};

}

#endif /* C_TIMER_HPP */