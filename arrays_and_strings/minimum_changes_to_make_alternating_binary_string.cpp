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

TEST(MinOperationsTest, SampleTest1)
{
    EXPECT_EQ(1, minOperationsFA("0100"));
}

TEST(MinOperationsTest, SampleTest2)
{
    EXPECT_EQ(0, minOperationsFA("10"));
}

TEST(MinOperationsTest, SampleTest3)
{
    EXPECT_EQ(2, minOperationsFA("1111"));
}
