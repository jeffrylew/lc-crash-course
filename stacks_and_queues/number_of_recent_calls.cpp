#include <gtest/gtest.h>

#include <queue>

static int ping(int t)
{
    static std::queue<int> queue;

    while (!queue.empty() && queue.front() < t - 3000)
    {
        queue.pop();
    }

    queue.push(t);
    return static_cast<int>(queue.size());
}

TEST(PingTest, SampleTest)
{
    EXPECT_EQ(1, ping(1));
    EXPECT_EQ(2, ping(100));
    EXPECT_EQ(3, ping(3001));
    EXPECT_EQ(3, ping(3002));
}