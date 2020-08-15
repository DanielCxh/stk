#ifndef C_WORKER_HPP
#define C_WORKER_HPP

#include <list>
#include <thread>
#include <atomic>
#include <condition_variable>
#include <thread/CTask.hpp>

namespace stk
{

class CWorker
{

public:
    using Ptr = std::shared_ptr<CWorker>;

public:
    CWorker(bool _fulltime = true, bool _overtime = false);
    ~CWorker();

    /*!
     * \brief   Add a new task to m_tasks and notify to process.
     */
    void Add(CTask::Ptr const & _task);
    // void Delete(CTask const & _task);

    // void OverWork(std::int32_t const _amount);


    bool IsIdle() const;

    bool IsRun() const;
    
    /*!
     * \brief   
     */
    void Sleep(int _time = -1);
    void Wakeup();


private:
    void onRunning();

    /*!
     * \brief   Get task from tasks, this function will block until could get a task from m_tasks.
     */
    CTask::Ptr getTask();
    
    void wait();

private:
    std::thread      m_thread;

    bool             m_fulltime { true };

    std::atomic_bool m_run  { false };
    std::atomic_bool m_idle { false };
    
    std::mutex              m_locker;
    std::condition_variable m_cv;

    std::list<CTask::Ptr> m_tasks;
};

}

#endif /* C_WORKER_HPP */
