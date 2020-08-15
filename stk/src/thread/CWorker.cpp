#include <iostream>
#include <thread/CWorker.hpp>

namespace stk
{

using Locker = std::unique_lock<std::mutex>;

CWorker::CWorker(bool _fulltime, bool _overtime)
    : m_fulltime { _fulltime }
{
    m_run.store(true);
    m_idle.store(true);

    m_thread = std::thread(&CWorker::onRunning, this);
    m_thread.detach();
}

CWorker::~CWorker()
{
    printf("destroy .... \n");
}

void CWorker::Add(CTask::Ptr const & _task)
{
    Locker lock { m_locker };

    m_idle.store(false);
    
    m_tasks.push_back(_task);
    
    m_locker.unlock();
    m_cv.notify_one();
}

bool CWorker::IsIdle() const
{
    return m_idle;
}

bool CWorker::IsRun() const
{
    return m_run;
}

void CWorker::onRunning()
{
    while (m_run)
    {
        // std::cout << std::this_thread::get_id() << std::endl;
        
        const CTask::Ptr & task = getTask();
     
        if (task)
        {
            task->Exec();
        }
        
        // remove front
        m_tasks.pop_front();

        if ( !m_fulltime && m_tasks.empty() )
        {
            /* stop running */
            m_run.store(false);
        }
    }
}

CTask::Ptr CWorker::getTask()
{
    wait();

    Locker locker { m_locker };

    if (!m_tasks.empty())
    {   
        return m_tasks.front();
    }
    
    return nullptr;
}

void CWorker::wait()
{
    Locker locker { m_locker };
    
    while(m_tasks.empty())
    {
        m_idle.store(true);

        m_cv.wait(locker);
    }
}

}
