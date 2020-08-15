#ifndef TEST_DEF_HPP
#define TEST_DEF_HPP

#include "./case/TestWorkThread.hpp"

#define TEST_MODE(mode) mTestList.push_back(new stk::test::mode());

/* Add test mode. */
#ifndef TEST_LIST
#define TEST_LIST()     \
TEST_MODE(TestWorkThread)
#endif

#endif