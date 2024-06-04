#include <gtest/gtest.h>

#include <string>
#include <vector>

//! @brief If numeric value of word[0, ..., i] is divisible by m then div[i] = 1
//! @param[in] word 0-indexed word of length n consisting of digits
//! @param[in] m    Positive integer to divide by
//! @return Vector div of length n consisting of 0 and 1
static std::vector<int> divisibilityArray(std::string word, int m)
{
    //! @details leetcode.com/problems/find-the-divisibility-array-of-a-string
    //!
    //!          Time complexity O(N) where N = word.size()
    //!          Space complexity O(1), excluding output vector div

    std::vector<int> div {};
    div.reserve(word.size());

    long curr {};

    for (const char digit : word)
    {
        curr = (curr * 10L + static_cast<long>(digit - '0')) % m;

        if (curr == 0)
        {
            div.push_back(1);
        }
        else
        {
            div.push_back(0);
        }
    }

    return div;
}

TEST(DivisibilityArrayTest, SampleTest1)
{
    const std::vector<int> expected_output {1, 1, 0, 0, 0, 1, 1, 0, 0};

    EXPECT_EQ(expected_output, divisibilityArray("998244353", 3));
}

TEST(DivisibilityArrayTest, SampleTest2)
{
    const std::vector<int> expected_output {0, 1, 0, 1};

    EXPECT_EQ(expected_output, divisibilityArray("1010", 10));
}
