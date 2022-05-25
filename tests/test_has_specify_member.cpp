#include "gtest/gtest.h"
#include <stack>
#include "has_specify_member.hpp"


TEST(has_specify_member_test, forstructure)
{
    std::stack<int> stints;
    EXPECT_TRUE(dlcpp::tpl_utils::HasSpecifyMember<std::stack<int>>::value);
}


class TestMember{
public:
    void run(void*){

    }
};

TEST(has_specify_member_test, forfunction)
{
    EXPECT_TRUE((dlcpp::tpl_utils::thread_rounter<TestMember,&TestMember::run>(0)== NULL));
}