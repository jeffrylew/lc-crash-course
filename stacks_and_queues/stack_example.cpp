#include <gtest/gtest.h>

#include <stack>

TEST(StackExampleTest, TestStack)
{
    std::stack<int> stack {};

    stack.push(1);
    stack.push(2);
    stack.push(3);

    EXPECT_EQ(3, stack.top());
    stack.pop();

    EXPECT_EQ(2, stack.top());
    stack.pop();

    EXPECT_EQ(1, stack.top());
    stack.pop();

    stack.push(5);
    EXPECT_FALSE(stack.empty());
}

