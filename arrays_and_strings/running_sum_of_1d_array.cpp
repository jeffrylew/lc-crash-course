#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<int> runningSumFA(std::vector<int> nums)
{
    std::vector<int> prefix {};
    prefix.reserve(nums.size());
    prefix.push_back(nums[0]);

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        prefix.push_back(nums[i] + prefix.back());
    }

    return prefix;
}

TEST(RunningSumTest, SampleTest)
{
    const std::vector<int> expected_output {1, 3, 6, 10};

    const auto resultFA = runningSumFA({1, 2, 3, 4});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultFA.cbegin()));
}