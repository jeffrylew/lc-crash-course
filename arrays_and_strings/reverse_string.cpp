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

TEST(ReverseStringTest, SampleTest)
{
    const std::vector<char> input {'h', 'e', 'l', 'l', 'o'};
    const std::vector<char> expected_output {'o', 'l', 'l', 'e', 'h'};

    auto s_fa = input;
    reverseStringFA(s_fa);

    EXPECT_TRUE(std::equal(expected_output.cbegin(),
                           expected_output.cend(),
                           s_fa.cbegin()));
}