#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <vector>

//! @brief Check if all piles can be eaten within h hours
//! @param[in] k     Eating speed (bananas per hour)
//! @param[in] limit Number of hours h to eat all bananas within
//! @param[in] piles Reference to vector of n piles of bananas
//! @return True if all bananas can be eaten in h hours with rate k, else false
static bool check(int k, long limit, const std::vector<int>& piles)
{
    //! @details Koko can only eat from one pile per hour
    //!
    //!          Time complexity O(N) where N = piles.size()

    long hours {};

    //! Can also use std::accumulate
    for (const int bananas : piles)
    {
        //! Determine how long it takes to get through the pile
        //! If there is one left over it will take an extra hour so round up
        hours += static_cast<long>(std::ceil(static_cast<double>(bananas) / k));
    }

    return hours <= limit;
}

//! @brief Get min k bananas/hr rate so all bananas can be eaten within h hours
//! @param[in] piles Vector of n piles of bananas
//! @param[in] h     Number of hours to eat all bananas within
//! @return Minimum rate k such that all bananas can be eaten within h hours
static int minEatingSpeed(std::vector<int> piles, int h)
{
    //! @details https://leetcode.com/problems/koko-eating-bananas/description/
    //!
    //!          Time complexity O(N * log k) where N = piles.size() and
    //!          k = max(piles). The binary search runs in O(log k) and during
    //!          each iteration, check is called which has O(N).
    //!          Space complexity O(1), no extra space is used.

    const auto limit = static_cast<long>(h);

    //! Eating speed cannot be lower than 1
    //! If eating speed is max(piles) then each pile will take 1 hr
    //! Our search space is [1, max(piles)]
    int left {1};
    int right {*std::max_element(piles.cbegin(), piles.cend())};

    /*
    for (const int bananas : piles)
    {
        right = std::max(right, bananas);
    }
    */

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (check(mid, limit, piles))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
}

TEST(MinEatingSpeedTest, SampleTest)
{
    EXPECT_EQ(4, minEatingSpeed({3, 6, 7, 11}, 8));

    EXPECT_EQ(30, minEatingSpeed({30, 11, 23, 4, 20}, 5));

    EXPECT_EQ(23, minEatingSpeed({30, 11, 23, 4, 20}, 6));
}