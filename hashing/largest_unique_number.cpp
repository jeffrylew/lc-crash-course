#include <gtest/gtest.h>

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

TEST(LargestUniqueNumberTest, SampleTest)
{
    const std::vector<int> input {5, 7, 3, 9, 4, 9, 8, 3, 1};

    EXPECT_EQ(8, largestUniqueNumberFA(input));
}