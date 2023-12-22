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

//! @brief DFS discussion solution to get ints of length n where digit diff is k
//! @param[in] n Length of each integer
//! @param[in] k Difference between two consecutive digits in int of length n
//! @return Vector of all integers of length n that satisfy digit differences k
static std::vector<int> numsSameConsecDiffDS1(int n, int k)
{
    //! @details https://leetcode.com/problems/
    //!          numbers-with-same-consecutive-differences/editorial/
    //!
    //!          Time complexity O(2 ^ N) where N = numer of digits for a valid
    //!          combination and K = difference between digits. For the highest
    //!          digit, there are 9 potential candidates and digits beyond have
    //!          at most 2 candidates for each position. Therefore, we have
    //!          9 * 2 ^ (N - 1) solutions at most for N > 1. The execution of
    //!          the algorithm results in a binary tree where each node is an
    //!          invocation of dfs(). The overall time complexity is
    //!          proportional to the number of nodes in the execution tree.
    //!          In the worst case, the total number of nodes in a binary tree
    //!          of depth N - 1 is 2 ^ N so overall time complexity is O(2 ^ N).
    //!          Note that when K = 0, there is only one possible digit at each
    //!          position. There would be 9 numbers in the output vector, where
    //!          each number has N digits. The time complexity would be O(N).
    //!          Space complexity O(2 ^ N). The max number of consecutive
    //!          recursive calls is N so the call stack space complexity is O(N)
    //!          but we use a list to keep all solutions, which could amount to
    //!          9 * 2 ^ (N - 1) elements. The overall space complexity is
    //!          O(N) + O(9 * 2 ^ (N - 1)) = O(2 ^ N).

    if (n == 1)
    {
        return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    std::vector<int> ans {};

    std::function<void(int, int)> dfs = [&](int remaining_N_digits, int num) {
        //! Base case
        if (remaining_N_digits == 0)
        {
            ans.push_back(num);
            return;
        }

        const int tail_digit {num % 10};

        std::vector<int> next_digits {tail_digit + k};
        if (k != 0)
        {
            next_digits.push_back(tail_digit - k);
        }

        for (const int next_digit : next_digits)
        {
            if (0 <= next_digit && next_digit < 10)
            {
                dfs(remaining_N_digits - 1, num * 10 + next_digit);
            }
        }
    };

    for (int num = 1; num < 10; ++num)
    {
        dfs(n - 1, num);
    }

    return ans;

} // static std::vector<int> numsSameConsecDiffDS1( ...

TEST(NumsSameConsecDiffTest, SampleTest1)
{
    const std::vector<int> expected_output {181, 292, 707, 818, 929};

    EXPECT_EQ(expected_output, numsSameConsecDiffFA(3, 7));
    EXPECT_EQ(expected_output, numsSameConsecDiffDS1(3, 7));
}

TEST(NumsSameConsecDiffTest, SampleTest2)
{
    const std::vector<int> expected_output {
        10, 12, 21, 23, 32, 34, 43, 45, 54, 56, 65, 67, 76, 78, 87, 89, 98};

    EXPECT_EQ(expected_output, numsSameConsecDiffFA(2, 1));
    EXPECT_EQ(expected_output, numsSameConsecDiffDS1(2, 1));
}
