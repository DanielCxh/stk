#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <vector>

namespace stk
{
namespace test
{

#define TF_START() {printf("===== [%s::%s] STARE\n", __FILE__, __FUNCTION__);
#define TF_END()   printf("===== [%s::%s] END\n\n",  __FILE__, __FUNCTION__);}

class TestBase
{

public:
    TestBase() = default;
    ~TestBase() = default;

    virtual void InitTest() = 0;
    virtual void DoTest() = 0;
    virtual void DestroyTest() = 0;
};

}
}

#endif /* TEST_BASE_HPP */
