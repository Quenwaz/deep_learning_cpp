#include "gtest/gtest.h"
#include <stack>
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future
#include <chrono>

void get_multiple_times(std::future<int>& fut) {
    int x = fut.get(); // 获取共享状态的值.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
    x = fut.get(); // 不能get 多次.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

void test_for_get_multiple_times()
{
    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t(get_multiple_times, std::ref(fut)); // 将 future 交给另外一个线程t.
    prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
}


// TEST(test_concurrency, promise_get_multiple_times)
// {
//     test_for_get_multiple_times();
//     EXPECT_TRUE(1);
// }

void set_multiple_times(std::future<int>& fut) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    int x = fut.get(); // 获取共享状态的值.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

void test_for_set_multiple_times()
{
    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t(set_multiple_times, std::ref(fut)); // 将 future 交给另外一个线程t.
    prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
    prom.set_value(100); // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
}

TEST(test_concurrency, promise_set_multiple_times)
{
    test_for_set_multiple_times();
    EXPECT_TRUE(1);
}




TEST(test_concurrency_DeathTest, promise)
{
    EXPECT_EXIT(test_for_get_multiple_times(), ::testing::ExitedWithCode(0), "");
    EXPECT_EXIT(test_for_set_multiple_times(), ::testing::ExitedWithCode(0), "");
}



