#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Helper function to compute the square
//! @param[in] num Integer to square
//! @pre |num| <= sqrt(std::numeric_limits<int>::max())
//! @return Input integer squared
static int square(int num)
{
    return num * num;
}

//! @brief First attempt solution
//! @param[in] nums Vector of integers in non-decreasing order (should be const)
//! @return Vector of squares of each element sorted in non-decreasing order
std::vector<int> sortedSquaresFA(std::vector<int>& nums)
{
    //! @details Space complexity O(nums_size)
    //!          Time complexity O(nums_size). In the worst case we will iterate
    //!          through nums twice when all elements are negative (2*nums_size)

    std::vector<int> output {};
    output.reserve(nums.size());
    
    const auto nums_size = static_cast<int>(nums.size());
    
    //! Tracks indices of natural numbers
    int natural_idx {};
    
    //! Tracks indices of negative numbers, initialize to -1
    //! to indicate no negative numbers have been found yet
    int negative_idx {-1};
    
    while (natural_idx < nums_size)
    {
        if (nums[natural_idx] < 0)
        {
            //! Found a negative number, keep searching for
            //! index of first natural number
            ++natural_idx;
        }
        else
        {
            //! Found a natural number so stop searching
            break;
        }
    }
    
    if (natural_idx > 0)
    {
        //! There is at least one negative number so
        //! set negative_idx to the last instance
        negative_idx = natural_idx - 1;
    }
    
    //! If there are negative and natural numbers,
    //! compare them before adding to output
    while (natural_idx < nums_size && negative_idx >= 0)
    {
        const auto nat_sq = square(nums[natural_idx]);
        const auto neg_sq = square(nums[negative_idx]);

        if (nat_sq == neg_sq)
        {
            output.emplace_back(nat_sq);
            output.emplace_back(neg_sq);
            ++natural_idx;
            --negative_idx;
        }
        else if (nat_sq < neg_sq)
        {
            output.emplace_back(nat_sq);
            ++natural_idx;
        }
        else
        {
            output.emplace_back(neg_sq);
            --negative_idx;
        }
        
    } // while (natural_idx < nums_size && ...
    
    //! Exhaust natural numbers
    while (natural_idx < nums_size)
    {
        output.emplace_back(square(nums[natural_idx++]));
    }
    
    //! Exhaust negative numbers
    while (negative_idx >= 0)
    {
        output.emplace_back(square(nums[negative_idx--]));
    }
    
    return output;

} // std::vector<int> sortedSquaresFA( ...

TEST(SortedSquaresTest, SampleTest)
{
    std::vector<int>       nums {-4, -1, 0, 3, 10};
    const std::vector<int> expected_output {0, 1, 9, 16, 100};

    const auto resultFA = sortedSquaresFA(nums);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultFA.cbegin()));
}