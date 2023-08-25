#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

//! @brief First attempt soln to get max num of apples that can be put in basket
//! @param[in] weight Vector of apple weights
//! @return Max number of apples that can be put in the basket of 5000 units
static int maxNumberOfApplesFA(std::vector<int> weight)
{
    std::priority_queue minHeap(
        weight.cbegin(), weight.cend(), std::greater<int>());

    int num_apples {};
    int remaining_units {5000};

    while (not minHeap.empty())
    {
        const int curr_weight {minHeap.top()};
        minHeap.pop();

        remaining_units -= curr_weight;
        if (remaining_units < 0)
        {
            break;
        }

        ++num_apples;
    }
    
    return num_apples;
}

//! @brief Discussion solution: sort
//! @param[in] weight Vector of apple weights
//! @return Max number of apples that can be put in the basket of 5000 units
static int maxNumberOfApplesDS1(std::vector<int> weight)
{
    //! @details https://leetcode.com/problems/
    //!          how-many-apples-can-you-put-into-the-basket/editorial/
    //!
    //!          Time complexity O(N * log N) where N = weight.size() for sort.
    //!          Space complexity O(log N) for quicksort variation (editorial
    //!          says O(1) because no additional data structures are used)

    std::sort(weight.begin(), weight.end());

    int apples {};
    int units {};

    for (const auto weight : weights)
    {
        units += weight;

        if (units > 5000)
        {
            break;
        }

        ++apples;
    }

    return apples;
}

TEST(MaxNumberOfApplesTest, SampleTest)
{
    EXPECT_EQ(4, maxNumberOfApplesFA({100, 200, 150, 1000}));
    EXPECT_EQ(4, maxNumberOfApplesDS1({100, 200, 150, 1000}));

    EXPECT_EQ(5, maxNumberOfApplesFA({900, 950, 800, 1000, 700, 800}));
    EXPECT_EQ(5, maxNumberOfApplesDS1({900, 950, 800, 1000, 700, 800}));
}