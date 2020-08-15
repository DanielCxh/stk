#include <thread/CWork.hpp>

namespace stk
{

/***********************************************************************************************************************
 * PUBLIC METHODS
 **********************************************************************************************************************/

CWork::Ptr CWork::Instance()
{
    static CWork::Ptr work = std::make_shared<CWork>();

    return work;
}

CWork::CWork()
{
    init();
}

CWork::~CWork()
{

}

void CWork::Push(CTask::Ptr & _task)
{
    /* if exist idle worker assign the task to it,
     * otherwise, push it to pool
     */
    CWorker::Ptr& worker = m_works.GetIdleWorker();
    worker->Add(_task);
}

/***********************************************************************************************************************
 * PRIVATE METHODS
 **********************************************************************************************************************/

void CWork::init()
{
    m_works.Create();
}

}


