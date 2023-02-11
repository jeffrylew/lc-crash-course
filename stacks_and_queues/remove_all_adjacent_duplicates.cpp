#include <gtest/gtest.h>

#include <string>

//! @brief Remove all adjacent duplicates in string
//! @param[in] s String potentially containing duplicate characters to remove
//! @return Input string without duplicates
static std::string removeDuplicates(std::string s)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /706/stacks-and-queues/4646/
    //!
    //!          Time complexity O(N), N = s.size()
    //!          Space complexity O(N)

    std::string ans {};

    for (char c : s)
    {
        if (not ans.empty() && ans.back() == c)
        {
            ans.pop_back();
        }
        else
        {
            ans.push_back(c);
        }
    }

    return ans;
}

TEST(RemoveDuplicatesTest, TestCase1)
{
    EXPECT_EQ("ca", removeDuplicates("abbaca"));
}

TEST(RemoveDuplicatesTest, TestCase2)
{
    EXPECT_EQ("ay", removeDuplicates("azxxzy"));
}