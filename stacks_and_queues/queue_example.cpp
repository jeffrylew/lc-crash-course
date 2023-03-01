#include <gtest/gtest.h>

#include <queue>

TEST(QueueExampleTest, TestQueue)
{
    std::queue<int> queue;

    queue.push(1);
    queue.push(2);
    queue.push(3);

    while (!queue.empty())
    {
        queue.pop();
    }

    EXPECT_TRUE(queue.empty());
}