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

//! @brief Discussion solution: min-heap
//! @param[in] weight Vector of apple weights
//! @return Max number of apples that can be put in the basket of 5000 units
static int maxNumberOfApplesDS2(std::vector<int> weight)
{
    //! @details https://leetcode.com/problems/
    //!          how-many-apples-can-you-put-into-the-basket/editorial/
    //!
    //!          Time complexity O(N + k*log N) where N = weight.size() and k is
    //!          the number of apples that will be put into the basket. O(N) to
    //!          transform the vector into a heap. Each pop operation is called
    //!          k times and costs O(log N).
    //!          Space complexity O(N) for min heap.

    std::priority_queue minHeap(
        weight.cbegin(), weight.cend(), std::greater<int>());
    
    int apples {};
    int units {};

    while (not minHeap.empty() && units + minHeap.top() <= 5000)
    {
        units += minHeap.top();
        minHeap.pop();

        ++apples;
    }

    return apples;
}

//! @brief Discussion solution: bucket sort
//! @param[in] weight Vector of apple weights
//! @return Max number of apples that can be put in the basket of 5000 units
static int maxNumberOfApplesDS3(std::vector<int> weight)
{
    //! @details https://leetcode.com/problems/
    //!          how-many-apples-can-you-put-into-the-basket/editorial/
    //!
    //!          Time complexity O(N + W) where N = weight.size() and W is the
    //!          largest element in weight. We iterate through weight and bucket
    //!          once and the lengths are N and W respectively.
    //!          Space complexity O(W) to initialize vector bucket with size of
    //!          max(weight).

    //! Initialize the bucket to store all elements
    const int size {*std::max_element(weight.cbegin(), weight.cend())};

    std::vector<int> bucket(size + 1);
    for (const int ele : weight)
    {
        ++bucket[ele];
    }

    int apples {};
    int units {};

    for (int i = 0; i < size + 1; ++i)
    {
        //! If we have apples of i units of weight
        if (bucket[i] != 0)
        {
            //! We need to make sure that
            //! 1. We do not take more apples than those provided
            //! 2. We do not exceed 5000 units of weight
            const int take {std::min(bucket[i], (5000 - units) / i)};

            if (take == 0)
            {
                break;
            }

            units += take * i;
            apples += take;
        }
    }

    return apples;
}

TEST(MaxNumberOfApplesTest, SampleTest)
{
    EXPECT_EQ(4, maxNumberOfApplesFA({100, 200, 150, 1000}));
    EXPECT_EQ(4, maxNumberOfApplesDS1({100, 200, 150, 1000}));
    EXPECT_EQ(4, maxNumberOfApplesDS2({100, 200, 150, 1000}));
    EXPECT_EQ(4, maxNumberOfApplesDS3({100, 200, 150, 1000}));

    EXPECT_EQ(5, maxNumberOfApplesFA({900, 950, 800, 1000, 700, 800}));
    EXPECT_EQ(5, maxNumberOfApplesDS1({900, 950, 800, 1000, 700, 800}));
    EXPECT_EQ(5, maxNumberOfApplesDS2({900, 950, 800, 1000, 700, 800}));
    EXPECT_EQ(5, maxNumberOfApplesDS3({900, 950, 800, 1000, 700, 800}));
}