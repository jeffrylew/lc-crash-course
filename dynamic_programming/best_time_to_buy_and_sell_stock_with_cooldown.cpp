#include <gtest/gtest.h>

#include <functional>
#include <vector>

static int maxProfitFA(std::vector<int> prices)
{
    //! @todo
}

TEST(MaxProfitTest, SampleTest1)
{
    EXPECT_EQ(3, maxProfitFA({1, 2, 3, 0, 2}));
}

TEST(MaxProfitTest, SampleTest2)
{
    EXPECT_EQ(0, maxProfitFA({1}));
}
