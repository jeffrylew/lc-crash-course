#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <unordered_map>
#include <vector>

static int getDigitSum(int num)
{
    int digitSum {};
    while (num > 0)
    {
        digitSum += num % 10;
        num /= 10;
    }

    return digitSum;
}

//! @brief Find max nums[i] + nums[j] where nums[i]/nums[j] have same digit sum
//! @param[in] num Vector of integers
//! @return Maximum value of nums[i] + nums[j]
static int maximumSum1(std::vector<int> nums)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /705/hashing/4645/
    //!
    //!          Identify groups by digit sum and add to hash map. Then iterate
    //!          over hash map and for each group with at least 2 elements, find
    //!          2 max elements by sorting
    //!
    //!          Time complexity O(N log N) due to sorting if every number in
    //!          input has the same digit sum where N = nums.size()
    //!          Space complexity O(N) to store all elements in hash map

    std::unordered_map<int, std::vector<int>> dic {};
    for (const int num : nums)
    {
        const int digitSum = getDigitSum(num);
        dic[digitSum].push_back(num);
    }

    int ans {-1};
    /*
    for (auto [key, curr] : dic)
    */
    for (auto kv : dic)
    {
        auto& curr = kv.second;
        if (curr.size() > 1ULL)
        {
            std::sort(curr.begin(), curr.end(), std::greater<int>());
            ans = std::max(ans, curr[0] + curr[1]);
        }
    }

    return ans;

} // static int maximumSum1( ...

//! @brief Find max nums[i] + nums[j] where nums[i]/nums[j] have same digit sum
//! @param[in] num Vector of integers
//! @return Maximum sum of nums[i] + nums[j] with equal sum of digits
static int maximumSum2(std::vector<int> nums)
{
    //! @details Don't need to store all numbers in group, only save largest
    //!          number seen so far for each digit sum.
    //!
    //!          Time complexity O(N) where average case uses less space since
    //!          each key only stores an int instead of a vector of ints. Save
    //!          on an extra iteration and sort in each iteration. N = nums.size
    //!          Space complexity O(N) for storing elements in hash map

    std::unordered_map<int, int> dic {};
    
    int ans {-1};

    for (const int num : nums)
    {
        const int digitSum = getDigitSum(num);
        if (dic.find(digitSum) != dic.end())
        {
            ans = std::max(ans, num + dic[digitSum]);
        }
        dic[digitSum] = std::max(dic[digitSum], num);
    }

    return ans;

} // static int maximumSum2( ...

TEST(MaximumSumTest, SampleTest)
{
    EXPECT_EQ(54, maximumSum1({18, 43, 36, 13, 7}));
    EXPECT_EQ(54, maximumSum2({18, 43, 36, 13, 7}));
}