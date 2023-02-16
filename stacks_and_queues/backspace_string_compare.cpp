#include <gtest/gtest.h>

#include <string>

//! @brief Helper function to simulate typing of string
//! @param[in] s String with characters to process
//! @return Output string with any backspaces processed
static std::string build(std::string s)
{
    std::string ans {};
    for (char c : s)
    {
        if (c != '#')
        {
            ans.push_back(c);
        }
        else if (not ans.empty())
        {
            ans.pop_back();
        }
    }

    return ans;
}

//! @brief Determine if strings are equal when typed into empty text editors
//! @param[in] s First string to compare, # means a backspace character
//! @param[in] t Second string to compare, # means a backspace character
//! @return Tue if strings are equal, else false
static bool backspaceCompare(std::string s, std::string t)
{
    return build(s) == build(t);
}

TEST(BackspaceCompareTest, TestCase1)
{
    EXPECT_TRUE(backspaceCompare("ab#c", "ad#c"));
}

TEST(BackspaceCompareTest, TestCase2)
{
    EXPECT_TRUE(backspaceCompare("ab##", "c#d#"));
}

TEST(BackspaceCompareTest, TestCase3)
{
    EXPECT_FALSE(backspaceCompare("a#c", "b"));
}