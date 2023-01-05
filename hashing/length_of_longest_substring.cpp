#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <unordered_map>

//! @brief Find length of longest substring without repeating characters
//! @param[in] s String to check
//! @return Length of longest substring without repeating characters
static int lengthOfLongestSubstringFA(std::string s)
{
    int substr_len {};
    int left {};

    std::unordered_map<char, int> char_count {};

    for (int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        //! Character count > 1 indicates a duplicate
        if (++char_count[s[right]] > 1)
        {
            while (left < right)
            {
                --char_count[s[left]];

                if (s[left++] == s[right])
                {
                    break;
                }
            }
        }

        substr_len = std::max(substr_len, right - left + 1);
    }

    return substr_len;

} // static int lengthOfLongestSubstringFA( ...

TEST(LengthOfLongestSubstringTest, SampleTest)
{
    EXPECT_EQ(3, lengthOfLongestSubstringFA("abcabcbb"));
}