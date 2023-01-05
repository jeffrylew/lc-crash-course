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

//! @brief Discussion solution to find length of longest substring
//! @param[in] s String to check
//! @return Length of longest substring without repeating characters
static int lengthOfLongestSubstringDS1(std::string s)
{
    //! @details https://leetcode.com/problems/
    //!          longest-substring-without-repeating-characters/solutions/
    //!          127839/official-solution/
    //!
    //!          Time complexity O(2N) = O(N) where N = s.size(). In the worst
    //!          case each character will be visited twice by left and right
    //!          Space complexity O(min(M, N)), need O(K) space for the sliding
    //!          window where K is size of hash map. K is upper bounded by
    //!          N = s.size() and M = size of the charset/alphabet

    std::unordered_map<char, int> char_count {};

    int left {};
    int right {};

    int substr_len {};
    while (right < static_cast<int>(s.size()))
    {
        while (++char_count[s[right]] > 1)
        {
            --char_count[s[left++]];
        }

        substr_len = std::max(substr_len, right - left + 1);
        ++right;
    }

    return substr_len;

} // static int lengthOfLongestSubstringDS1( ...

//! @brief Optimized discussion solution to find length of longest substring
//! @param[in] s String to check
//! @return Length of longest substring without repeating characters
static int lengthOfLongestSubstringDS2(std::string s)
{
    //! @details https://leetcode.com/problems/
    //!          longest-substring-without-repeating-characters/solutions/
    //!          127839/official-solution/
    //!
    //!          Time complexity O(N) where N = s.size(). Index left iterates
    //!          N times.
    //!          Space complexity O(min(M, N)), need O(K) space for the sliding
    //!          window where K is size of hash map. K is upper bounded by
    //!          N = s.size() and M = size of the charset/alphabet

    int substr_len {};
    int left {};

    std::unordered_map<char, int> char_idx {};

    for (int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        if (char_idx[s[right]] > 0)
        {
            left = std::max(char_idx[s[right]], left);
        }

        substr_len        = std::max(substr_len, right - left + 1);
        char_idx[s[right]] = right + 1;
    }

    return substr_len;

} // static int lengthOfLongestSubstringDS2( ...

TEST(LengthOfLongestSubstringTest, SampleTest)
{
    EXPECT_EQ(3, lengthOfLongestSubstringFA("abcabcbb"));
    EXPECT_EQ(3, lengthOfLongestSubstringDS1("abcabcbb"));
    EXPECT_EQ(3, lengthOfLongestSubstringDS2("abcabcbb"));
}