#include <map>
#include <iostream>

#include <utils/CEnvironment.hpp>
#include <utils/CLogger.hpp>
#include <utils/CTimer.hpp>
#include <utils/CEvent.hpp>

#include <thread/CWork.hpp>

#include "./case/TestBase.hpp"
#include "TestDef.hpp"


using namespace stk;
using namespace test;

#define TEST_FUNC_DEF(module) \
        void test##_##module(bool _enable)

#define TEST_FUNC_CAL(module, enable) \
        test##_##module(enable)

#define TEST_FUNC_START(module) \
        void test##_##module(bool _enable) \
        { \
            if (false == _enable) return; \
            std::cout << ">>>>>> [" << __func__ << "] START" << std::endl;

#define TEST_FUNC_END() \
        std::cout << "\n<<<<<< [" << __func__ << "] END\n" << std::endl; }


TEST_FUNC_DEF(CLogger);
TEST_FUNC_DEF(CEnvironment);
TEST_FUNC_DEF(CTimer);
TEST_FUNC_DEF(CWork);

std::vector<TestBase*> mTestList;

void running()
{
    TEST_LIST();

    for (unsigned int i = 0U; i < mTestList.size(); ++i)
    {
        if (mTestList[i])
        {
            mTestList[i]->InitTest();
            mTestList[i]->DoTest();
        }
    }
}


int main(int argc, char * argv[])
{
    std::cout << "===== TEST START ===" << std::endl << std::endl;
    
    TEST_FUNC_CAL(CLogger, false);
    TEST_FUNC_CAL(CEnvironment, false);
    TEST_FUNC_CAL(CTimer, false);
    TEST_FUNC_CAL(CWork, false);

    std::thread thread = std::thread(&running);
    thread.join();

    std::cout << "===== TEST END =====" << std::endl;

    return 0;
}

TEST_FUNC_START(CTimer)

    CTimer timer([](){ printf("call ontimer...\n"); }, 1000, -1, true);

    for (;;);

TEST_FUNC_END()


TEST_FUNC_START(CLogger)

    CLogger() << 999 << ", abc" << ",123" << endl();
    CLogD() << 111 << 1.2f << endl();
    CLogger::SetColorfull(true);
    CLogI("TE") << "info" << 1.2f << endl();
    CLogW("X") << "wwwww" << 1.2f << endl();
    CLogE() << "error" << 1.2f << endl();

TEST_FUNC_END()


TEST_FUNC_START(CEnvironment)
{
    std::string file = "./config.ini";

    if (ENV()->Init(file))
    {
        std::cout << ENV()->Get("a") << std::endl;
        std::cout << ENVGET(b) << std::endl;
        std::cout << ENVGET(c) << std::endl;
        std::cout << ENV()->Get("d") << std::endl;
        std::cout << ENV()->Get("e") << std::endl;
        std::cout << ENV()->Get("f") << std::endl;

        ENVSET(k, "hello");
        ENVSET(k, "hello4");
        ENV()->Set("g", "ggggg");
        std::cout << ENV()->Get("k") << std::endl;
        std::cout << ENV()->Get("g") << std::endl;
    }

    TEST_FUNC_END()
}

TEST_FUNC_START(CWork)
    CTask::Ptr a = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeee1\n");});

     
    CTask::Ptr b = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeeb\n");});
    CTask::Ptr c = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeec\n");});
    CTask::Ptr d = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeed\n");});
    CTask::Ptr e = std::make_shared<CTask>([](){printf("eeeee5\n");});
   CTask::Ptr f = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeef\n");});
    CTask::Ptr g = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeeg\n");});
    CTask::Ptr h = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 100; ++i)
        {
            printf("eeeeeh\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        });
    CTask::Ptr i = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        printf("eeeeei\n");});

    CTask::Ptr k = std::make_shared<CTask>([](){ 
        for (int i = 0; i < 10; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        printf("eeeeekkkkk\n");});

    CWork::Instance()->Push(a);
    CWork::Instance()->Push(b);
    CWork::Instance()->Push(c);
    CWork::Instance()->Push(d);
    CWork::Instance()->Push(e);
    CWork::Instance()->Push(f);
    CWork::Instance()->Push(g);
    CWork::Instance()->Push(h);
    CWork::Instance()->Push(i);
    CWork::Instance()->Push(k);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    CTask::Ptr aa = std::make_shared<CTask>([](){ printf("eeeee1aa\n");});
    CTask::Ptr bb = std::make_shared<CTask>([](){ printf("eeeee1bb\n");});

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    CTask::Ptr cc = std::make_shared<CTask>([](){ printf("eeeee1cc\n");});
    CTask::Ptr dd = std::make_shared<CTask>([](){ printf("eeeee1dd\n");});

    CWork::Instance()->Push(aa);
    CWork::Instance()->Push(bb);
    CWork::Instance()->Push(cc);
    CWork::Instance()->Push(dd);


    for (int i = 0; i < 10000; ++i)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "===== tick =====" << std::endl;
    }
TEST_FUNC_END()
