#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

static std::vector<int> runningSumFA(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/running-sum-of-1d-array/
    //!          solutions/1136761/official-solution/
    //!
    //!          Time complexity O(N) where N = nums.size()
    //!          Space complexity O(1), output array space not considered

    std::vector<int> prefix {};
    prefix.reserve(nums.size());
    prefix.push_back(nums[0]);

    for (int i = 1; i < static_cast<int>(nums.size()); ++i)
    {
        prefix.push_back(nums[i] + prefix.back());
    }

    return prefix;
}

static std::vector<int> runningSumDS(std::vector<int> nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        //! Result at index i is sum of result at i-1 and element at i
        nums[i] += nums[i - 1];
    }
    return nums;
}

TEST(RunningSumTest, SampleTest)
{
    const std::vector<int> expected_output {1, 3, 6, 10};

    const auto resultFA = runningSumFA({1, 2, 3, 4});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultFA.cbegin()));

    const auto resultDS = runningSumDS({1, 2, 3, 4});

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDS.cbegin()));
}