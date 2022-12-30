#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

//! @brief First attempt solution to find largest integer that only occurs once
//! @param[in] nums Vector of integers
//! @return Largest integer that only occurs once or -1
static int largestUniqueNumberFA(std::vector<int> nums)
{
    std::unordered_map<int, int> counts {};

    for (const auto num : nums)
    {
        ++counts[num];
    }

    int largestNum {-1};
    for (const auto& kv : counts)
    {
        if (largestNum < kv.first && kv.second == 1)
        {
            largestNum = kv.first;
        }
    }

    return largestNum;

} // static int largestUniqueNumberFA( ...

//! @brief Discussion solution to find largest integer that only occurs once
//! @param[in] nums Vector of integers
//! @return Largest integer that only occurs once or -1
static int largestUniqueNumberDS(std::vector<int> nums)
{
    //! @details https://leetcode.com/problems/largest-unique-number/solutions/
    //!          1102562/official-solution/
    //!
    //!          Time complexity O(N) where N = nums.size()
    //!          Space complexity O(N) since in worst case is unique numbers

    std::unordered_map<int, int> count {};
    for (const int i : nums)
    {
        ++count[i];
    }

    int result {-1};
    /*
    for (auto [key, val] : count)
    */
    for (const auto& kv : count)
    {
        if (kv.second == 1)
        {
            result = std::max(result, kv.first);
        }
    }
    return result;

} // static int largestUniqueNumberDS( ...

TEST(LargestUniqueNumberTest, SampleTest)
{
    const std::vector<int> input {5, 7, 3, 9, 4, 9, 8, 3, 1};

    EXPECT_EQ(8, largestUniqueNumberFA(input));
    EXPECT_EQ(8, largestUniqueNumberDS(input));
}