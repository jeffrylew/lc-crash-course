#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <unordered_map>

//! @brief Find length of longest substring that has at most k distinct chars
//! @param[in] s String to search
//! @param[in] k Max number of distinct characters in substring
//! @return Length of longest substring
static int findLongestSubstring(std::string s, int k)
{
    //! @details Time complexity O(N), N = s.size()
    //!          Space complexity O(k) since delete elements from map beyond k

    std::unordered_map<char, int> counts;

    int left {};
    int ans {};

    for (int right = 0; right < static_cast<int>(s.size()); ++right)
    {
        ++counts[s[right]];

        while (static_cast<int>(counts.size()) > k)
        {
            --counts[s[left]];
            if (counts[s[left]] == 0)
            {
                counts.erase(s[left]);
            }
            ++left;
        }

        ans = std::max(ans, right - left + 1);

    } // for (int right = 0; ...

    return ans;

} // static int findLongestSubstring( ...

TEST(FindLongestSubstringTest, SampleTest)
{
    EXPECT_EQ(2, findLongestSubstring("eceba", 2));
}