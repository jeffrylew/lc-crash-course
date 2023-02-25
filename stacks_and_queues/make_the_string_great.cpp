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

//! @brief Iterative solution from LC discussion section
//! @param[in] s String containing lower and upper case letters
//! @return A good string
static std::string makeGoodDS1(std::string s)
{
    //! @details https://leetcode.com/problems/make-the-string-great/editorial/
    //!
    //!          Time complexity O(N^2) where N = s.size(). Each iteration for s
    //!          takes O(N) time. Worst case scenario remove one pair each
    //!          iterations, there might be O(N) pairs
    //!
    //!          Space complexity O(N) for making copies of rest of s

    //! If s has less than 2 characters, return it
    while (s.size() > 1)
    {
        //! Flag to record if we find any pair to remove
        bool find {};

        //! Check every two adjacent chars, currChar and nextChar
        for (int i = 0; i < s.size() - 1; ++i)
        {
            char currChar {s[i]};
            char nextChar {s[i + 1]};

            //! If they make a pair, remove them from s and set find flag
            if (std::abs(currChar - nextChar) == 32)
            {
                s    = s.substr(0, i) + s.substr(i + 2);
                find = true;
                break;
            }
        }

        //! If cannot find any pair to remove, break the loop
        if (not find)
        {
            break;
        }
    }
    return s;

} // static std::string makeGoodDS1( ...

TEST(MakeGoodTest, SampleTest)
{
    EXPECT_EQ("leetcode", makeGoodFA("leEeetcode"));
    EXPECT_EQ("", makeGoodFA("Pp"));

    EXPECT_EQ("leetcode", makeGoodDS1("leEeetcode"));
    EXPECT_EQ("", makeGoodDS1("Pp"));
}