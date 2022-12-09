#include <gtest/gtest.h>

#include <vector>

static bool checkForTarget(std::vector<int>& nums, int target)
{
    int left {};
    int right {nums.size() - 1};

    while (left < right)
    {
        auto curr = nums[left] + nums[right];
        if (curr == target)
        {
            return true;
        }
        
        if (curr > target)
        {
            --right;
        }
        else
        {
            ++left;
        }
    }
    
    return false;

} // static bool checkForTarget( ...

TEST(CheckForTargetTest, SampleTest)
{
    EXPECT_TRUE(checkForTarget({1, 2, 4, 6, 8, 9, 14, 15}, 13));
}
