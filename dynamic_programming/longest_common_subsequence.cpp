#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

//! @brief Top down DP solution to get length of longest common subsequence
//! @param[in] text1 First string
//! @param[in] text2 Second string
//! @return Length of longest common subsequence between text1 and text2
static int longestCommonSubsequenceDS1(std::string text1, std::string text2)
{
    //! @details leetcode.com/problems/longest-common-subsequence/description/
    //!
    //!          Time complexity O(M * N), M = text1.size() and N = text2.size()
    //!          Space complexity O(M * N)

    std::vector<std::vector<int>> memo(
        text1.size(), std::vector<int>(text2.size(), -1));

    //! Get length of LCS starting at idx1 of text1 and idx2 of text2
    std::function<int(int, int)> get_lcs = [&](int idx1, int idx2) -> int {
        //! At least one string has been exhausted. No characters are remaining,
        //! there cannot be any common characters so return 0
        if (idx1 == static_cast<int>(text1.size())
            || idx2 == static_cast<int>(text2.size()))
        {
            return 0;
        }

        if (memo[idx1][idx2] != -1)
        {
            return memo[idx1][idx2];
        }

        int length {};

        //! Found a match in characters - move to next character in both strings
        if (text1[idx1] == text2[idx2])
        {
            length = 1 + get_lcs(idx1 + 1, idx2 + 1);
        }
        else
        {
            //! Either move to next char in text1 or move to next char in text2
            length = std::max(get_lcs(idx1 + 1, idx2), get_lcs(idx1, idx2 + 1));
        }

        return memo[idx1][idx2] = length;
    };

    return get_lcs(0, 0);

} // static int longestCommonSubsequenceDS1( ...

//! @brief First attempt bottom up DP solution, pretty much matches editorial
//! @param[in] text1 First string
//! @param[in] text2 Second string
//! @return Length of longest common subsequence between text1 and text2
static int longestCommonSubsequenceFA(std::string text1, std::string text2)
{
    //! @details leetcode.com/problems/longest-common-subsequence/description/
    //!
    //!          Time complexity O(M * N), M = text1.size() and N = text2.size()
    //!          Space complexity O(M * N)

    std::vector<std::vector<int>> lcs(
        text1.size() + 1U, std::vector<int>(text2.size() + 1U, 0));

    for (auto idx1 = static_cast<int>(text1.size()) - 1; idx1 >= 0; --idx1)
    {
        for (auto idx2 = static_cast<int>(text2.size()) - 1; idx2 >= 0; --idx2)
        {
            if (text1[idx1] == text2[idx2])
            {
                lcs[idx1][idx2] = 1 + lcs[idx1 + 1][idx2 + 1];
            }
            else
            {
                lcs[idx1][idx2] =
                    std::max(lcs[idx1 + 1][idx2], lcs[idx1][idx2 + 1]);
            }
        }
    }

    return lcs[0][0];

} // static int longestCommonSubsequenceFA( ...

TEST(LongestCommonSubsequenceTest, SampleTest1)
{
    EXPECT_EQ(3, longestCommonSubsequenceDS1("abcde", "ace"));
    EXPECT_EQ(3, longestCommonSubsequenceFA("abcde", "ace"));
}

TEST(LongestCommonSubsequenceTest, SampleTest2)
{
    EXPECT_EQ(3, longestCommonSubsequenceDS1("abc", "abc"));
    EXPECT_EQ(3, longestCommonSubsequenceFA("abc", "abc"));
}

TEST(LongestCommonSubsequenceTest, SampleTest3)
{
    EXPECT_EQ(0, longestCommonSubsequenceDS1("abc", "def"));
    EXPECT_EQ(0, longestCommonSubsequenceFA("abc", "def"));
}
