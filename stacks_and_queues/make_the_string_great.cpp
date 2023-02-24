#include <gtest/gtest.h>

#include <cctype>
#include <string>

//! @brief Remove two adjacent characters that make string bad until it is good
//! @param[in] s String containing lower and upper case letters
//! @return A good string
static std::string makeGoodFA(std::string s)
{
    std::string output {};

    for (const char c : s)
    {
        if (not output.empty()
            && ((std::isupper(c) != 0 && output.back() == std::tolower(c))
                || (std::islower(c) != 0 && output.back() == std::toupper(c))))
        {
            //! Remove last element from output and skip adding c
            output.pop_back();
        }
        else
        {
            //! Either output is empty or c can be added
            output.push_back(c);
        }
    }

    return output;
}

TEST(MakeGoodTest, SampleTest)
{
    EXPECT_EQ("leetcode", makeGoodFA("leEeetcode"));
    EXPECT_EQ("", makeGoodFA("Pp"));
}