#include "gtest/gtest.h"
#include "functors_as_ordinary_functions.hpp"

class TestClass{
public:
    void run()
    {

    }
};

TEST(functors_as_ordinary_functions, t1)
{
    tpl_utils::Callback<void(void*)>::fn_agent_ = [](void* d) {
        TestClass test = *(TestClass*)d;
        test.run();
    };
    void(*TestFn)(void*) = static_cast<decltype(TestFn)>(tpl_utils::Callback<void(void*)>::Function);
    TestClass test;
    TestFn(&test);
    EXPECT_TRUE(true);
}