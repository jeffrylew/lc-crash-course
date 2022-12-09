#include <gtest/gtest.h>

#include <string>

static bool checkIfPalindrome(std::string s)
{
    int left {};
    int right {s.size() - 1}; // Assuming s isn't empty

    while (left < right)
    {
        if (s[left] != s[right])
        {
            return false;
        }
        
        ++left;
        --right;
    }
    
    return true;
}

TEST(CheckIfPalindromeTest, SampleTest)
{
    EXPECT_TRUE(checkIfPalindrome("racecar"));
    EXPECT_FALSE(checkIfPalindrome("aceba"));
}