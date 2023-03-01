#include <gtest/gtest.h>

#include <cctype>
#include <cmath>
#include <string>
#include <vector>

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

//! @brief Recursive solution from LC discussion section
//! @param[in] s String containing lower and upper case letters
//! @return A good string
static std::string makeGoodDS2(std::string s)
{
    //! @details Time complexity O(N^2), takes O(N) to iterate through s to find
    //!          pair to remove and in worst-case there will be O(N) pairs
    //!
    //!          Space complexity O(N^2), space complexity proportional to max
    //!          depth of recursion tree. We have up to N/2 pairs which is a
    //!          recursion tree of depth O(N). Each function call takes O(N)
    //!          space so overall complexity is O(N^2)

    //! If the string is empty, just return it
    if (s.empty())
    {
        return s;
    }

    //! If we find a pair in s, remove this pair from s
    //! and solve the remaining string recursively
    for (int i = 0; i < size() - 1; ++i)
    {
        if (std::abs(s[i] - s[i + 1]) == 32)
        {
            return makeGoodDS2(s.substr(0, i) + s.substr(i + 2));
        }
    }

    //! Base case, if we can't find a pair, just return s
    return s;
}

//! @brief Stack solution from LC discussion section
//! @param[in] s String containing lower and upper case letters
//! @return A good string
static std::string makeGoodDS3(std::string s)
{
    //! @details Time complexity O(N)
    //!          Space complexity O(N)

    //! Use stack to store the visited characters
    std::vector<char> stack;

    //! Iterate over s
    for (const auto currChar : s)
    {
        //! If the current char makes a pair with the last char in the stack,
        //! remove both of them. Otherwise, add the current char to stack
        if (not stack.empty() && std::abs(stack.back() - currChar) == 32)
        {
            stack.pop_back();
        }
        else
        {
            stack.push_back(currChar);
        }
    }

    //! Return string concatenated by all chars left in stack
    std::string ans {stack.begin(), stack.end()};
    return ans;
}

//! @brief Two pointers solution from LC discussion section
//! @param[in] s String containing lower and upper case letters
//! @return A good string
static std::string makeGoodDS4(std::string s)
{
    //! @details Time complexity O(N), only iterate once over s and update two
    //!          pointers which takes constant time.
    //!          Space complexity O(1) since modify input string in place

    //! Initialize end = 0 since the good string is empty
    int end {};

    for (int cur = 0; cur < s.size(); ++cur)
    {
        //! If s[cur] makes a pair with the last char s[end - 1] in good string,
        //! remove s[end - 1] by decrementing end by 1
        //! Else, add s[cur] to the good string by overwriting s[end] by s[cur]
        if (end > 0 && std::abs(s[cur] - s[end - 1]) == 32)
        {
            --end;
        }
        else
        {
            s[end++] = s[cur];
        }
    }

    //! Once the iteration ends, the string before end is the good string
    return s.substr(0, end);
}

TEST(MakeGoodTest, SampleTest)
{
    EXPECT_EQ("leetcode", makeGoodFA("leEeetcode"));
    EXPECT_EQ("", makeGoodFA("Pp"));

    EXPECT_EQ("leetcode", makeGoodDS1("leEeetcode"));
    EXPECT_EQ("", makeGoodDS1("Pp"));

    EXPECT_EQ("leetcode", makeGoodDS2("leEeetcode"));
    EXPECT_EQ("", makeGoodDS2("Pp"));

    EXPECT_EQ("leetcode", makeGoodDS3("leEeetcode"));
    EXPECT_EQ("", makeGoodDS3("Pp"));

    EXPECT_EQ("leetcode", makeGoodDS4("leEeetcode"));
    EXPECT_EQ("", makeGoodDS4("Pp"));
}