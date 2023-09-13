#include <gtest/gtest.h>

#include <vector>

//! @brief Get index of target if found or the index where it would be inserted
//! @param[in] num    Reference to vector of sorted integers
//! @param[in] target Number to get index of
//! @return Index of target if found or index where it would be inserted
static int searchInsertFA(const std::vector<int>& nums, int target)
{
    int left {};
    int right {static_cast<int>(nums.size()) - 1};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (nums[mid] == target)
        {
            return mid;
        }

        if (nums[mid] < target)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return left;

} // static int searchInsertFA( ...

TEST(SearchInsertTest, SampleTest)
{
    const std::vector<int> input {1, 3, 5, 6};

    EXPECT_EQ(2, searchInsertFA(input, 5));
    EXPECT_EQ(1, searchInsertFA(input, 2));
    EXPECT_EQ(4, searchInsertFA(input, 7));
}