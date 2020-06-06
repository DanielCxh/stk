#ifndef C_THREAD_POOL_HPP
#define C_THREAD_POOL_HPP

#include <map>

template<T>
class CThreadPool
{

public:
    void Create(int size);

private:
    void runLoop();

private:
    std::map<int, CTask, std::greater<int> > m_tasks;
};

#endif /* C_THREAD_POOL_HPP */