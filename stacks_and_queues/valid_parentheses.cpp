#include <gtest/gtest.h>

#include <stack>
#include <string>
#include <unordered_map>

//! @brief Determine if input string is valid
//! @param[in] s String containing characters '(', ')', '{', '}', '[', ']'
//! @return True if string is valid, else false
static bool isValid(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /706/stacks-and-queues/4646/
    //!
    //!          Time complexity O(N) where N is size of input string
    //!          Space complexity O(N), stack size grows linearly with input

    std::stack<char>               stack;
    std::unordered_map<char, char> matching {{'(', ')'},
                                             {'{', '}'},
                                             {'[', ']'}};
    
    for (char c : s)
    {
        if (matching.find(c) != matching.cend())
        {
            stack.push(c);
        }
        else
        {
            if (stack.empty())
            {
                return false;
            }

            char previousOpening = stack.top();
            if (matching[previousOpening] != c)
            {
                return false;
            }

            stack.pop();
        }
    }

    return stack.empty();

} // static bool isValid( ...

TEST(IsValidTest, Case1)
{
    EXPECT_TRUE(isValid("()"));
}

TEST(IsValidTest, Case2)
{
    EXPECT_TRUE(isValid("()[]{}"));
}

TEST(IsValidTest, Case3)
{
    EXPECT_FALSE(isValid("(]"));
}