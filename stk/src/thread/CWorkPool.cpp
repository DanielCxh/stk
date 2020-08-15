#include <iostream>
#include <thread/CWorkPool.hpp>

namespace stk
{

void CWorkPool::Create(int size)
{
    int cupThreadSize = ( (size == 0) ? std::thread::hardware_concurrency() : size );

    for (int i = 0; i < cupThreadSize; ++i)
    {
        CWorker::Ptr work = std::make_shared<CWorker>();
        m_works.push_back(work);
    }

    /*
     * m_works[0] used for block actions, deal with sync mode tasks.
     */

    std::cout << "[CWorkPool::Create] cup thread size = " << cupThreadSize << std::endl;
}

CWorker::Ptr &CWorkPool::GetIdleWorker()
{
    /* remove not run works in m_tempWorks */
    for (auto it = m_tempWorks.begin(); it != m_tempWorks.end(); )
    {
        if (!(*it)->IsRun())
        {
            it = m_tempWorks.erase(it);
        }
        else
        {
            ++it;
        }
    }

    /* find a idle thread to process task */
    for (int i = 0; i < m_works.size(); ++i)
    {
        if (m_works[i]->IsIdle())
        {
            return m_works[i];
        }
    }

    /* If all the workre is working, create a new temporarily worker. */
    CWorker::Ptr work = std::make_shared<CWorker>(false);
    m_tempWorks.push_back(work);

    return m_tempWorks.back();
}

int CWorkPool::GetPoolSize() const
{
    return m_works.size();
}

}
