#include <gtest/gtest.h>

#include <algorithm>
#include <string>

//! @brief First attempt to get min num of operations to make string alternating
//! @param[in] s String consisting only of characters '0' and '1'
//! @return Min number of operations needed to make binary string alternating
static int minOperationsFA(std::string s)
{
    //! @details https://leetcode.com/problems/
    //!         minimum-changes-to-make-alternating-binary-string
    //!
    //!         Time complexity O(N) where N = s.size()
    //!         Space complexity O(1)

    int zero_one_ops {};
    int one_zero_ops {};

    for (int idx = 0; idx < static_cast<int>(s.size()); ++idx)
    {
        if (idx % 2 == 0)
        {
            // Even indices
            (s[idx] == '0') ? ++one_zero_ops : ++zero_one_ops;
        }
        else
        {
            // Odd indices
            (s[idx] == '0') ? ++zero_one_ops : ++one_zero_ops;
        }
    }

    return std::min(zero_one_ops, one_zero_ops);

} // static int minOperationsFA( ...

//! @brief Start with zero or start with one discussion solution
//! @param[in] s String consisting only of characters '0' and '1'
//! @return Min number of operations needed to make binary string alternating
static int minOperationsDS1(std::string s)
{
    //! @details https://leetcode.com/problems/
    //!         minimum-changes-to-make-alternating-binary-string
    //!
    //!         Time complexity O(n) where n = s.size()
    //!         Space complexity O(1)

    int start0 {};
    int start1 {};

    for (int i = 0; i < static_cast<int>(s.size()); i++)
    {
        if (i % 2 == 0)
        {
            if (s[i] == '0')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
        else
        {
            if (s[i] == '1')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
    }

    return std::min(start0, start1);

} // static int minOperationsDS1( ...

TEST(MinOperationsTest, SampleTest1)
{
    EXPECT_EQ(1, minOperationsFA("0100"));
    EXPECT_EQ(1, minOperationsDS1("0100"));
}

TEST(MinOperationsTest, SampleTest2)
{
    EXPECT_EQ(0, minOperationsFA("10"));
    EXPECT_EQ(0, minOperationsDS1("10"));
}

TEST(MinOperationsTest, SampleTest3)
{
    EXPECT_EQ(2, minOperationsFA("1111"));
    EXPECT_EQ(2, minOperationsDS1("1111"));
}
