#ifndef C_WORKER_HPP
#define C_WORKER_HPP

#include <map>
#include <thread/CTask.hpp>

class CWorker
{

public:
    using Ptr = std::shared_ptr<CWorker>;

public:
    void Add(CTask const & _task);
    void Delete(CTask const & _task);


private:

    std::map<int, CTask, std::greater<int> > m_tasks;
};

#endif /* C_WORK_HPP */