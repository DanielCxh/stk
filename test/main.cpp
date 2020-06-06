#include <iostream>
#include <utils/CEnvironment.hpp>
#include <utils/CLogger.hpp>
#include <utils/CTimer.hpp>
#include <utils/CEvent.hpp>

#include <map>

using namespace stk;

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


int main(int argc, char * argv[])
{
    std::cout << "===== TEST START ===" << std::endl << std::endl;
    
    TEST_FUNC_CAL(CLogger, false);
    TEST_FUNC_CAL(CEnvironment, false);
    TEST_FUNC_CAL(CTimer, false);

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