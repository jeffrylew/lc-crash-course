#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <unordered_map>

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

TEST(MaxNumberOfBalloonsTest, SampleTest)
{
    EXPECT_EQ(1, maxNumberOfBalloonsFA("nlaebolko"));
}