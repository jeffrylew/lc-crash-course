#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

static std::vector<int> twoSum(std::vector<int> nums, int target)
{
    std::unordered_map<int, int> dic;

    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        const int num        = nums[i];
        const int complement = target - num;
        if (dic.find(complement) != dic.cend())
        {
            return {i, dic[complement]};
        }

        dic[num] = i;
    }

    return {-1, -1};

} // static std::vector<int> twoSum( ...

TEST(TwoSumTest, SampleTest)
{
    const std::vector<int> expected_output {0, 4};

    const auto result = twoSum({5, 2, 7, 10, 3, 9}, 8);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           result.cbegin()));
}