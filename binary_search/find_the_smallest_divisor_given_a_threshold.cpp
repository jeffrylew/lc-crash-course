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

//! @brief Discussion Solution: Linear Search (naive approach)
//! @param[in] nums      Vector of integers
//! @param[in] threshold Sum of vector elements divided by divisor must be less
//! @return Smallest divisor so sum of ele after dividing by it is <= threshold
static int smallestDivisorDS1(std::vector<int> nums, int threshold)
{
    //! @details https://leetcode.com/problems/
    //!          find-the-smallest-divisor-given-a-threshold/editorial/
    //!
    //!          Time complexity O(N * M) where N = nums.size(), M = max(nums)
    //!          We iterate on all possible divisors and for each divisor, we
    //!          iterate on the whole nums vector to find sum which takes O(N).
    //!          For M divisors, it takes O(N * M).
    //!          Space complexity O(1)

    const int maxElement {*std::max_element(nums.begin(), nums.end())};

    //! Iterate on all divisors
    for (int divisor = 1; divisor <= maxElement; ++divisor)
    {
        int  sumOfDivisionResults {};
        bool thresholdExceeded {};

        //! Divide all numbers of array and sum the result
        for (int num : nums)
        {
            sumOfDivisionResults += std::ceil((1.0 * num) / divisor);

            // Another way to round division result to nearest ceil int
            // sumOfDivisionResults = (num + divisor - 1) / divisor;

            if (sumOfDivisionResults > threshold)
            {
                thresholdExceeded = true;
                break;
            }
        }

        //! If threshold was not exceeded then return current divisor
        if (not thresholdExceeded)
        {
            return divisor;
        }
    }

    return -1;

} // static int smallestDivisorDS1( ...

//! @brief Helper function to return the sum of division results with divisor
//! @param[in] nums    Reference to vector of integers
//! @param[in] divisor Positive double
//! @return Sum of division results with divisor
static int findDivisionSum(const std::vector<int>& nums, int divisor)
{
    int result {};

    for (int num : nums)
    {
        result += std::ceil((1.0 * num) / divisor);
    }

    return result;
}

//! @brief Discussion Solution: Binary Search
//! @param[in] nums      Vector of integers
//! @param[in] threshold Sum of vector elements divided by divisor must be less
//! @return Smallest divisor so sum of ele after dividing by it is <= threshold
static int smallestDivisorDS2(std::vector<int> nums, int threshold)
{
    //! @details https://leetcode.com/problems
    //!          /find-the-smallest-divisor-given-a-threshold/editorial/
    //!
    //!          Time complexity O(N * log M) where N = nums.size() and
    //!          M = max(nums). We reduce the search space of possible divisors
    //!          by half. There are log M levels so iterate on log M divisors.
    //!          For each divisor, iterate on entire nums array to find division
    //!          result sum, which takes O(N).
    //!          Space complexity O(1)

    int ans {-1};

    int low {1};
    int high {*std::max_element(nums.cbegin(), nums.cend())};

    //! Iterate using binary search on all divisors
    while (low <= high)
    {
        const int mid {(low + high) / 2};
        const int result {findDivisionSum(nums, mid)};

        //! If curent divisor does not exceed threshold then it can be answer.
        //! Also try smaller divisors, changing search space to left half.
        if (result <= threshold)
        {
            ans  = mid;
            high = mid - 1;
        }
        else
        {
            //! Otherwise need a bigger divisor to reduce the result sum.
            //! Change search space to right half.
            low = mid + 1;
        }
    }

    return ans;

} // static int smallestDivisorDS2( ...

TEST(SmallestDivisorTest, SampleTest1)
{
    EXPECT_EQ(5, smallestDivisorFA({1, 2, 5, 9}, 6));
    EXPECT_EQ(5, smallestDivisorDS1({1, 2, 5, 9}, 6));
    EXPECT_EQ(5, smallestDivisorDS2({1, 2, 5, 9}, 6));

    EXPECT_EQ(44, smallestDivisorFA({44, 22, 33, 11, 1}, 5));
    EXPECT_EQ(44, smallestDivisorDS1({44, 22, 33, 11, 1}, 5));
    EXPECT_EQ(44, smallestDivisorDS2({44, 22, 33, 11, 1}, 5));
}
