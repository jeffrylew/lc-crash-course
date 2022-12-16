#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
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
static std::vector<int> sortedSquaresFA(std::vector<int>& nums)
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

} // static std::vector<int> sortedSquaresFA( ...

//! @brief First discussion solution using std::sort
//! @param[in] nums Vector of integers in non-decreasing order (should be const)
//! @return Vector of squares of each element sorted in non-decreasing order
static std::vector<int> sortedSquaresDS1(std::vector<int>& nums)
{
    //! @details https://leetcode.com/problems/squares-of-a-sorted-array/
    //!          solutions/221849/official-solution/
    //!
    //!          Time complexity O(N log N) where N = nums.size() since need
    //!          to iterate through nums once and std::sort has average case
    //!          linearithmic O(N log N) time complexity. So O(N) + O(N log N)
    //!          is O(N log N).
    //!          Space complexity O(N)

    const auto       N = nums.size();
    std::vector<int> output(N);

    for (std::size_t i = 0ULL; i < N; ++i)
    {
        output[i] = nums[i] * nums[i];
    }

    std::sort(output.begin(), output.end());
    return output;

} // static std::vector<int> sortedSquaresDS1( ...

//! @brief Second discussion solution using two pointers
//! @param[in] nums Vector of integers in non-decreasing order (should be const)
//! @return Vector of squares of each element sorted in non-decreasing order
static std::vector<int> sortedSquaresDS2(std::vector<int>& nums)
{
    //! @details Time complexity O(N) where N = nums.size()
    //!          Space complexity O(N) if take output into account, else O(1)

    std::vector<int> output(nums.size());
    const auto       N = static_cast<int>(nums.size());

    int left {};
    int right {N - 1};

    //! Populating output vector from back so want to fill biggest squares first
    for (int i = N - 1; i >= 0; --i)
    {
        int square;
        if (std::abs(nums[left]) < std::abs(nums[right]))
        {
            square = nums[right--];
        }
        else
        {
            square = nums[left++];
        }
        result[i] = square * square;
    }

    return result;

} // static std::vector<int> sortedSquaresDS2( ...

TEST(SortedSquaresTest, SampleTest)
{
    std::vector<int>       nums {-4, -1, 0, 3, 10};
    const std::vector<int> expected_output {0, 1, 9, 16, 100};

    const auto resultFA = sortedSquaresFA(nums);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultFA.cbegin()));
    
    const auto resultDS1 = sortedSquaresDS1(nums);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDS1.cbegin()));
    
    const auto resultDS2 = sortedSquaresDS2(nums);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           resultDS2.cbegin()));
}