#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <vector>

//! @brief Helper function checks if divisor applied to nums satisfies threshold
//! @param[in] nums      Reference to vector of integers
//! @param[in] threshold Sum of vector elements divided by divisor must be less
//! @param[in] divisor   Positive double
//! @return True if divisor applied to nums satisfies threshold, else false
static bool checkFA(const std::vector<int>& nums, int threshold, double divisor)
{
    return std::accumulate(nums.cbegin(),
                           nums.cend(),
                           0,
                           [divisor](int lhs, int rhs) -> int {
                               const auto rhsdbl = static_cast<double>(rhs);
                               const auto result = std::ceil(rhsdbl / divisor);

                               return lhs + static_cast<int>(result);
                           })
        <= threshold;
}

//! @brief First attempt to get smallest divisor so result is <= threshold
//! @param[in] nums      Vector of integers
//! @param[in] threshold Sum of vector elements divided by divisor must be less
//! @return Smallest divisor so sum of ele after dividing by it is <= threshold
static int smallestDivisorFA(std::vector<int> nums, int threshold)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /710/binary-search/4694/
    //!
    //!          Time complexity O(N * log k) where N = nums.size() and
    //!          k = max(nums). It takes O(N) to find max in nums and O(N) for
    //!          checkFA which sums all elements divided by divisor in nums.
    //!          The latter occurs O(log k) times due to the binary search.
    //!          Space complexity O(1).

    //! Smallest divisor is 1 (left) and largest divisor is max in nums (right)
    int left {1};
    int right {*std::max_element(nums.cbegin(), nums.cend())};

    while (left <= right)
    {
        //! mid = divisor
        const int mid {left + (right - left) / 2};

        if (checkFA(nums, threshold, static_cast<double>(mid)))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;

} // static int smallestDivisorFA( ...

TEST(SmallestDivisorTest, SampleTest1)
{
    EXPECT_EQ(5, smallestDivisorFA({1, 2, 5, 9}, 6));

    EXPECT_EQ(44, smallestDivisorFA({44, 22, 33, 11, 1}, 5));
}