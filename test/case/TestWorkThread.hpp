#ifndef TEST_WORK_THREAD_HPP
#define TEST_WORK_THREAD_HPP

#include "TestBase.hpp"

namespace stk
{
namespace test
{

class TestWorkThread : public TestBase
{

public:
    void InitTest()
    TF_START()
        printf("TestWorkThread::InitTest\n");
    TF_END()

    void DoTest()
    TF_START()
        printf("TestWorkThread::DoTest\n");
    TF_END()

    void DestroyTest()
    {

    }
};

}
}

#endif