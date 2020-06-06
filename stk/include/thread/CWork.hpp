#ifndef C_WORK_HPP
#define C_WORK_HPP


#include <thread/CThreadPool.hpp>

class CWork
{

public:
    static CWork & Instance();

    void Async();
    void Sync();

    void Start();
    void Push();

private:
    CWork();
    ~CWork();

    void onRunning();
    void exit();

private:
    int m_threadNum;

    CThreadPool m_syncPool;
    CThreadPool m_asyncPool;
};

#endif /* C_WORK_HPP */