#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <string>
#include <unordered_map>
#include <utility>

//! @brief First attempt solution to find max number of instances of "balloon"
//! @param[in] text String to search
//! @return Max instances of "balloon"
static int maxNumberOfBalloonsFA(std::string text)
{
    std::unordered_map<char, int> counts {};
    for (char letter : text)
    {
        ++counts[letter];
    }

    constexpr int num_b {1};
    constexpr int num_a {1};
    constexpr int num_l {2};
    constexpr int num_o {2};
    constexpr int num_n {1};

    return std::min({counts['b'] / num_b,
                     counts['a'] / num_a,
                     counts['l'] / num_l,
                     counts['o'] / num_o,
                     counts['n'] / num_n});

} // static int maxNumberOfBalloonsFA( ...

static int findMaxNumberofPattern(std::string text, std::string pattern)
{
    //! @details https://leetcode.com/problems/maximum-number-of-balloons/
    //!          solutions/1388850/maximum-number-of-balloons/
    //!
    //!          Let N = text.size(), M = pattern.size(), K = max number of
    //!          distinct letters in pattern
    //!          Time complexity O(N + M), traverse over text and pattern to
    //!          find frequency of each character. Then traverse over frequency
    //!          arrays of length K to find bottleneck character but K = 26
    //!          Space complexity O(1) since frequency arrays require O(K) space
    //!          but K = 26 for lowercase English letters

    std::array<int, 26> freqInText {{}};
    std::array<int, 26> freqInPattern {{}};

    //! Frequency of chars in text
    for (char c : text)
    {
        ++freqInText[c - 'a'];
    }

    //! Frequency of chars in pattern
    for (char c : pattern)
    {
        ++freqInPattern[c - 'a'];
    }

    int answer {std::numeric_limits<int>::max()};

    //! Compare the max string that can be produced considering
    //! one character at a time
    for (int i = 0; i < 26; ++i)
    {
        //! Do not divide by zero
        if (freqInPattern[i] != 0)
        {
            answer = std::min(answer, freqInText[i] / freqInPattern[i]);
        }
    }

    return answer;

} // static int findMaxNumberofPattern( ...

//! @brief Discussion solution to find max number of instances of "balloon"
//! @param[in] text String to search
//! @return Max instances of "balloon"
static int maxNumberOfBalloonsDS(std::string text)
{
    return findMaxNumberofPattern(std::move(text), "balloon");
}

TEST(MaxNumberOfBalloonsTest, SampleTest)
{
    EXPECT_EQ(1, maxNumberOfBalloonsFA("nlaebolko"));
    EXPECT_EQ(1, maxNumberOfBalloonsDS("nlaebolko"));
}