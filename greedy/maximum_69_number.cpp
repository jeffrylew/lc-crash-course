#include <gtest/gtest.h>

#include <cmath>
#include <stack>
#include <string>

//! @brief First attempt solution to get max num by changing at most one digit
//! @param[in] num Positive int consisting only of digits 6 and 9
//! @return Max number by changing at most one digit (6 -> 9 or 9-> 6)
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

//! @brief Discussion solution: Convert the integer to an iterable object
//! @param[in] num Positive int consisting only of digits 6 and 9
//! @return Max number by changing at most one digit (6 -> 9 or 9-> 6)
static int maximum69NumberDS1(int num)
{
    //! @details https://leetcode.com/problems/maximum-69-number/editorial/
    //!
    //!          Time complexity O(L) where L = max number of digits nums has.
    //!          It takes O(L) to convert nums to an equivalent object and back.
    //!          Space complexity O(L) to create an object of length L.

    //! Convert the input to a string numString
    const auto numString = std::to_string(num);

    //! Iterate over the string from high to low
    for (auto& currChar : numString)
    {
        //! If find the first 6, replace it with 9 and break the loop
        if (currChar == '6')
        {
            currChar = '9';
            break;
        }
    }

    //! Convert the modified string to integer and return it
    return std::stoi(numString);
}

//! @brief Discussion solution: Check the remainder
//! @param[in] num Positive int consisting only of digits 6 and 9
//! @return Max number by changing at most one digit (6 -> 9 or 9-> 6)
static int maximum69NumberDS2(int num)
{
    //! @details https://leetcode.com/problems/maximum-69-number/editorial/
    //!
    //!          Time complexity O(L) where L = max number of digits nums has.
    //!          Need to perform L integer divisions at most, taking O(L) time.
    //!          Space complexity O(1)

    //! Since we start with the lowest digit, initialize currDigit = 0
    int numCopy {num};
    int idxFirstSix {-1};
    int currDigit {};

    //! Check every digit of numCopy from low to high
    while (numCopy > 0)
    {
        //! if current digit is 6, record it as the highest digit for 6
        if (numCopy % 10 == 6)
        {
            idxFirstSix = currDigit;
        }
        
        //! Move on to next digit
        numCopy /= 10;
        ++currDigit;
    }
    
    //! If don't find any digit of 6, return the original number
    //! Else, increment num by the difference made by the first 6
    return idxFirstSix == -1 ? num : num + 3 * std::pow(10, idxFirstSix);
}

TEST(Maximum69NumberTest, SampleTest)
{
    EXPECT_EQ(9969, maximum69NumberFA(9669));
    EXPECT_EQ(9969, maximum69NumberDS1(9669));
    EXPECT_EQ(9969, maximum69NumberDS2(9669));

    EXPECT_EQ(9999, maximum69NumberFA(9996));
    EXPECT_EQ(9999, maximum69NumberDS1(9996));
    EXPECT_EQ(9999, maximum69NumberDS2(9996));

    EXPECT_EQ(9999, maximum69NumberFA(9999));
    EXPECT_EQ(9999, maximum69NumberDS1(9999));
    EXPECT_EQ(9999, maximum69NumberDS2(9999));
}