#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <vector>

//! @brief First attempt to get vector of ints of len n where digit diff is k
//! @param[in] n Length of each integer
//! @param[in] k Difference between two consecutive digits in int of length n
//! @return Vector of all integers of length n that satisfy digit differences k
static std::vector<int> numsSameConsecDiffFA(int n, int k)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /711/backtracking/4695/
    //!
    //!          Time complexity O(10 ^ n) where n = length of each integer
    //!          Space complexity O(n)

    std::vector<int> ans {};
    std::vector<int> curr_digits {};

    std::function<void(int)> backtrack = [&](int idx) {
        if (static_cast<int>(curr_digits.size()) == n)
        {
            // pow is the power of ten that is multiplied by each digit
            int pow {n - 1};
            ans.push_back(std::accumulate(curr_digits.cbegin(),
                                          curr_digits.cend(),
                                          0,
                                          [&](int num, int digit) {
                                              return num
                                                  + digit * std::pow(10, pow--);
                                          }));
            return;
        }

        for (int digit = 0; digit < 10; ++digit)
        {
            if (idx == 0 && digit == 0)
            {
                continue;
            }

            if (curr_digits.empty())
            {
                curr_digits.push_back(digit);
            }
            else if (std::abs(digit - curr_digits[idx - 1]) == k)
            {
                curr_digits.push_back(digit);
            }
            else
            {
                continue;
            }

            backtrack(idx + 1);

            curr_digits.pop_back();
        }
    };

    backtrack(0);
    return ans;

} // static std::vector<int> numsSameConsecDiffFA( ...

TEST(NumsSameConsecDiffTest, SampleTest1)
{
    const std::vector<int> expected_output {181, 292, 707, 818, 929};

    EXPECT_EQ(expected_output, numsSameConsecDiffFA(3, 7));
}

TEST(NumsSameConsecDiffTest, SampleTest2)
{
    const std::vector<int> expected_output {
        10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98};

    EXPECT_EQ(expected_output, numsSameConsecDiffFA(2, 1));
}
