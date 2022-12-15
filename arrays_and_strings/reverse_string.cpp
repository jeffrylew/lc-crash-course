#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt solution
//! @param[in,out] s Vector of chars to reverse
static void reverseStringFA(std::vector<char>& s)
{
    if (s.empty())
    {
        return;
    }

    int  left {};
    auto right = static_cast<int>(s.size()) - 1;

    while (left < right)
    {
        std::swap(s[left], s[right]);
        ++left;
        --right;
    }

} // static void reverseStringFA( ...

//! @brief First discussion solution
//! @param[in,out] s Vector of chars to reverse
static void reverseStringDS1(std::vector<char>& s)
{
    std::reverse(s.begin(), s.end());
}

//! @brief Recursive helper function for second discussion solution
//! @param[in,out] s     Vector of chars to reverse
//! @param[in]     left  Left index/pointer
//! @param[in]     right Right index/pointer
static void DS2Helper(std::vector<char>& s, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    
    //! Could also use std::swap(s[left++], s[right--]) here
    auto tmp   = s[left];
    s[left++]  = s[right];
    s[right--] = tmp;

    DS2Helper(s, left, right);

} // static void DS2Helper( ...

//! @brief Second discussion solution, in-place recursion
//! @param[in,out] s Vector of chars to reverse
static void reverseStringDS2(std::vector<char>& s)
{
    //! @details https://leetcode.com/problems/reverse-string/solutions/404367/
    //!          official-solution/
    //!
    //!          Space complexity O(s.size()) due to recursion stack
    //!          Time complexity O(s.size()) to perform s.size()/2 swaps

    DS2Helper(s, 0, static_cast<int>(s.size()) - 1);
}

TEST(ReverseStringTest, SampleTest)
{
    const std::vector<char> input {'h', 'e', 'l', 'l', 'o'};
    const std::vector<char> expected_output {'o', 'l', 'l', 'e', 'h'};

    auto s_fa = input;
    reverseStringFA(s_fa);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           s_fa.cbegin()));
    
    auto s_ds1 = input;
    reverseStringDS1(s_ds1);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           s_ds1.cbegin()));
    
    auto s_ds2 = input;
    reverseStringDS2(s_ds2);
    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           s_ds2.cbegin()));
}