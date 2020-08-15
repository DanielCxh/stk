#ifndef C_WORK_POOL_HPP
#define C_WORK_POOL_HPP

#include <vector>
#include <thread/CWorker.hpp>

namespace stk
{

class CWorkPool
{

public:
    void Create(int size = 0);

    CWorker::Ptr &GetIdleWorker();

    int GetPoolSize() const;

private:
    // void runLoop();

private:
    std::vector<CWorker::Ptr> m_works;
    std::vector<CWorker::Ptr> m_tempWorks;
};

}

#endif /* C_WORK_POOL_HPP */
