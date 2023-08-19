#include <gtest/gtest.h>

#include <cmath>
#include <stack>

//! @brief Get max number by changing at most one digit (6 -> 9 or 9-> 6)
//! @param[in] num Positive int consisting only of digits 6 and 9
//! @return Max number by changing at most one digit
static int maximum69NumberFA(int num)
{
    std::stack<int> digits {};
    while (num > 0)
    {
        digits.push(num % 10);
        num /= 10;
    }

    int  max_num {};
    bool changed_digit {};

    while (not digits.empty())
    {
        if (not changed_digit && digits.top() == 6)
        {
            digits.top()  = 9;
            changed_digit = true;
        }
        
        max_num +=
            digits.top() * std::pow(10, static_cast<int>(digits.size()) - 1);
        digits.pop();
    }
    
    return max_num;
}

TEST(Maximum69NumberTest, SampleTest)
{
    EXPECT_EQ(9969, maximum69NumberFA(9669));

    EXPECT_EQ(9999, maximum69NumberFA(9996));

    EXPECT_EQ(9999, maximum69NumberFA(9999));
}