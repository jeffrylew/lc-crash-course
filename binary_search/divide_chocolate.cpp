#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

//! @brief Get max total sweetness of piece by cutting bar optimally
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessFA(std::vector<int> sweetness, int k)
{
    //! @details This solution is incorrect

    const auto sweet_size = static_cast<int>(sweetness.size());
    auto       prefix_sum = sweetness;

    for (int i = 1; i < sweet_size; ++i)
    {
        prefix_sum[i] += prefix_sum[i - 1];
    }

    //! Largest chunk size
    int largest_chunk {sweet_size - k};

    //! Keep track of maximum of minimum total sweetness
    int min_total_sweetness {std::numeric_limits<int>::max()};

    while (largest_chunk > 0)
    {
        int left {};
        for (int right = largest_chunk; right < sweet_size; ++right)
        {
            min_total_sweetness =
                std::min(min_total_sweetness,
                         std::accumulate(prefix_sum.begin() + left,
                                         prefix_sum.begin() + right,
                                         0));
            ++left;
        }

        --largest_chunk;
        left = 0;
    }

    return min_total_sweetness;
}

//! @brief Get max total sweetness of piece by cutting bar optimally
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessDS(std::vector<int> sweetness, int k)
{
    //! @details https://leetcode.com/problems/divide-chocolate/editorial/
    //!
    //!          Time complexity O(N * log (S / (k + 1))) where N = number of
    //!          chunks (sweetness.size()) and S = total sweetness of the bar.
    //!          The lower and upper bounds are min(sweetness) and S / (k + 1)
    //!          respectively. In the worst case when k is small, the right
    //!          boundary will have the same magnitude as S and the left
    //!          boundary will be 1. Thus, the maximum possible time complexity
    //!          for a single binary search is O(log S). For each search, need
    //!          to traverse the chocolate bar in order to allocate chunks to
    //!          everyone, which takes O(N).
    //!          Space complexity O(1). For each search, just need to count the
    //!          number of people who receive a piece of chocolate with enough
    //!          sweetess and the total chocolate sweetness for the current
    //!          person. Both use constant space.

    //! Initialize the left and right boundaries
    //! left  = 1
    //! right = total sweetness / number of people
    const int numPeople {k + 1};
    int       left {*std::min_element(sweetness.cbegin(), sweetness.cend())};
    int       right {
        std::accumulate(sweetness.cbegin(), sweetness.cend(), 0) / numPeople};

    while (left < right)
    {
        //! Get the middle index between left and right boundary indices
        //! curSweetness        = total sweetness for the current person
        //! peopleWithChocolate = number of people that have a piece of
        //! chocolate with sweetness greater than or equal to mid
        const int mid {(left + right + 1) / 2};
        int       curSweetness {};
        int       peopleWithChocolate {};

        //! Start assigning chunks to the current people
        for (const int chunk_sweetness : sweetness)
        {
            curSweetness += chunk_sweetness;

            //! When the total sweetness is no less than mid,
            //! move onto assigning chunks to the next person
            if (curSweetness >= mid)
            {
                ++peopleWithChocolate;
                curSweetness = 0;
            }
        }

        //! Check if we successfully gave everyone a piece of chocolate with
        //! sweetness no less than mid and eliminate the search space by half
        if (peopleWithChocolate >= numPeople)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    //! Once the left and right boundaries coincide, we find
    //! the target value which is the maximum possible sweetness
    return right;

} // static int maximizeSweetnessDS( ...

//! @brief Second attempt to get max total sweetness of piece by optimal cutting
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessSA(std::vector<int> sweetness, int k)
{
    //! @details This second attempt based off the discussion solution more
    //!          closely matches binarySearch() in binary_search_templates.cpp

    //! Initialize the left and right boundaries
    //! left  = 1
    //! right = total sweetness / number of people
    const int numPeople {k + 1};
    int       left {*std::min_element(sweetness.cbegin(), sweetness.cend())};
    int       right {
        std::accumulate(sweetness.cbegin(), sweetness.cend(), 0) / numPeople};

    int max_min_total_sweetness {};

    //! If left < right is used then SampleTest3 fails (outputs 4 instead of 5)
    while (left <= right)
    {
        //! Get the middle index between left and right boundary indices
        //! curSweetness        = total sweetness for the current person
        //! peopleWithChocolate = number of people that have a piece of
        //! chocolate with sweetness greater than or equal to mid
        const int mid {left + (right - left) / 2};
        int       curSweetness {};
        int       peopleWithChocolate {};

        //! Start assigning chunks to the current people
        for (const int chunk_sweetness : sweetness)
        {
            curSweetness += chunk_sweetness;

            //! When the total sweetness is no less than mid,
            //! move onto assigning chunks to the next person
            if (curSweetness >= mid)
            {
                ++peopleWithChocolate;
                curSweetness = 0;
            }
        }

        //! Check if we successfully gave everyone a piece of chocolate with
        //! sweetness no less than mid and eliminate the search space by half
        if (peopleWithChocolate >= numPeople)
        {
            max_min_total_sweetness = mid;
            left                    = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }

    return max_min_total_sweetness;

} // static int maximizeSweetnessSA( ...

TEST(MaximizeSweetnessTest, SampleTest1)
{
    const std::vector<int> sweetness {1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_NE(6, maximizeSweetnessFA(sweetness, 5));
    EXPECT_EQ(6, maximizeSweetnessDS(sweetness, 5));
    EXPECT_EQ(6, maximizeSweetnessSA(sweetness, 5));
}

TEST(MaximizeSweetnessTest, SampleTest2)
{
    const std::vector<int> sweetness {5, 6, 7, 8, 9, 1, 2, 3, 4};

    EXPECT_EQ(1, maximizeSweetnessFA(sweetness, 8));
    EXPECT_EQ(1, maximizeSweetnessDS(sweetness, 8));
    EXPECT_EQ(1, maximizeSweetnessSA(sweetness, 8));
}

TEST(MaximizeSweetnessTest, SampleTest3)
{
    const std::vector<int> sweetness {1, 2, 2, 1, 2, 2, 1, 2, 2};

    EXPECT_NE(5, maximizeSweetnessFA(sweetness, 2));
    EXPECT_EQ(5, maximizeSweetnessDS(sweetness, 2));
    EXPECT_EQ(5, maximizeSweetnessSA(sweetness, 2));
}
