#include <gtest/gtest.h>

#include <string>

static bool isSubsequence(std::string s, std::string t)
{
    //! @details Time complexity O(s.size() + t.size()), space complexity O(1)

    int i = 0, j = 0;
    while (i < s.size() && j < t.size())
    {
        if (s[i] == t[j])
        {
            ++i;
        }
        ++j;
    }
    
    return i == s.size();
}

TEST(IsSubsequenceTest, SampleTest)
{
    EXPECT_TRUE(isSubsequence("ace", "abcde"));
}