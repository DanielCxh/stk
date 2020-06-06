#include <utils/CTimer.hpp>

namespace stk
{

static constexpr unsigned int TIMER_LOOP_TIME = 10U; /* 10ms */ 

CTimer::CTimer(OnTimerFunc _func, int _interval, int _cnt, bool _auto_start)
            : m_func     { _func }
            , m_interval { _interval }
            , m_cnt      { _cnt }
            , m_inited   { false }
            , m_running  { _auto_start }
            , m_step     { 0 }
            , m_tick     { 0 }
{
    if (_auto_start)
    {
        createThread();
    }
}

CTimer::~CTimer()
{
    exit();
}

void CTimer::Start()
{
    if (m_inited)
    {
        m_running = true;
    }
    else
    {
        createThread();
    }
}

void CTimer::Stop()
{
    if (m_inited)
    {
        m_running = false;
        m_step = 0;
        m_tick = 0;
    }
}

void CTimer::Pause()
{
    if (m_inited)
    {
        m_running = false; 
    }
}

void CTimer::createThread()
{
    m_running = true;

    m_thread = std::thread(&CTimer::onRunning, this);
    m_thread.detach();

    m_inited = true;
}

void CTimer::onRunning()
{
    m_step = 0;
    m_tick = 0;
    int const maxTick = m_interval / TIMER_LOOP_TIME;

    while (m_running)
    {
        /* sleep 10ms for each loop */
        std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_LOOP_TIME));

        if ( (++m_tick) >= maxTick )
        {
            m_step++;

            m_func();

            if ( (m_step >= m_cnt) && (m_cnt != -1) )
            {
                exit();
                break;
            }

            m_tick = 0;
        }
    }
}

void CTimer::exit()
{
    m_running = false;

    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

}