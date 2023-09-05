#include <gtest/gtest.h>

#include <vector>

//! @brief Get index of target in nums if it exists, else return -1
//! @param[in] nums   Vector of ints sorted in ascending order
//! @param[in] target Target int to find index of
//! @return Index of target in nums if present, else -1
static int search(std::vector<int> nums, int target)
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

        if (nums[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return -1;

} // static int search( ...

TEST(SearchTest, SampleTest)
{
    EXPECT_EQ(4, search({-1, 0, 3, 5, 9, 12}, 9));

    EXPECT_EQ(-1, search({-1, 0, 3, 5, 9, 12}, 2));
}