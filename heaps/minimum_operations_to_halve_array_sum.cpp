#include <gtest/gtest.h>

#include <numeric>
#include <queue>
#include <vector>

static int halveArray(std::vector<int> nums)
{
    std::priority_queue<double> heap(nums.begin(), nums.end());

    double target {std::accumulate(nums.cbegin(), nums.cend(), 0.0) / 2.0};

    int ans {};
    while (target > 0.0)
    {
        ++ans;

        const double x {heap.top()};
        heap.pop();

        target -= x / 2.0;
        heap.push(x / 2.0);
    }

    return ans;
}

TEST(HalveArrayTest, SampleTest)
{
    EXPECT_EQ(3, halveArray({5, 19, 8, 1}));

    EXPECT_EQ(3, halveArray({3, 8, 20}));
}