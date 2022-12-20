#include <gtest/gtest.h>

#include <vector>

//! @brief Get number of ways to split array such that LHS sum >= RHS sum
//! @param[in] nums Vector of integers
//! @return Number of ways to split input
static int waysToSplitArray1(std::vector<int> nums)
{
    //! @details Time complexity O(N) since prefix sums allow LHS/RHS sums to be
    //!          evaluated in O(1)
    //!          Space complexity O(N) for prefix sum vector

    const auto nums_size = static_cast<int>(nums.size());

    std::vector<long> prefix = {nums[0]};
    for (int i = 1; i < nums_size; ++i)
    {
        prefix.push_back(nums[i] + prefix.back());
    }

    int ans {};
    for (int i = 0; i < nums_size - 1; ++i)
    {
        long leftSection = prefix[i];
        long rightSection = prefix.back() - prefix[i];
        if (leftSection >= rightSection)
        {
            ++ans;
        }
    }

    return ans;

} // static int waysToSplitArray1( ...

TEST(WaysToSplitArrayTest, SampleTest)
{
    EXPECT_EQ(2, waysToSplitArray1({10, 4, -8, 7}));
}