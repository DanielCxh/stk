#ifndef C_WORK_HPP
#define C_WORK_HPP

#include <memory>
#include <thread/CWorkPool.hpp>

namespace stk
{

class CWork
{
public:

    using Ptr = std::shared_ptr<CWork>;

public:
    static CWork::Ptr Instance();

    void Push(CTask::Ptr & _task);


    CWork();
    ~CWork();

private:
    
    /*!
     * \brief Used to init the work threads.
     */
    void init();

    /*!
     * \brief 
     */
    // void onRunning();
    // void exit();

    // void assignTask();

private:
    CWorkPool m_works;
};

}

#endif /* C_WORK_HPP */
