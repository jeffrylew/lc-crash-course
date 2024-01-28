#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get fewest number of coins to create amount
//! @param[in] coins Vector of coins of different denominations
//! @param[in] amount Target total amount of money
//! @return Fewest number of coins to make amount or -1 if cannot create amount
static int coinChangeFA(std::vector<int> coins, int amount)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /712/dynamic-programming/4581/
    //!
    //!          This solution is incorrect.

    //! Sort denominations in descending order
    std::sort(coins.begin(), coins.end(), std::greater {});

    //! Memoize fewest number of coins to make amount represented by index
    std::vector<int> memo(amount + 1, -1);
    memo[0] = 0;

    for (const int denomination : coins)
    {
        memo[denomination] = 1;
    }

    std::function<int(int)> dp = [&](int curr_amount) -> int {
        if (curr_amount < 0)
        {
            return -1;
        }

        //! Smallest denomination is still larger than curr_amount
        if (coins.back() > curr_amount)
        {
            return -1;
        }

        if (memo[curr_amount] != -1)
        {
            return memo[curr_amount];
        }

        for (const int denomination : coins)
        {
            if (denomination > curr_amount)
            {
                continue;
            }

            return memo[curr_amount] = 1 + dp(curr_amount - denomination);
        }

        //! Don't think this condition would be hit
        return -1;
    };

    return dp(amount);

} // static int coinChangeFA( ...

TEST(CoinChangeTest, SampleTest1)
{
    EXPECT_EQ(3, coinChangeFA({1, 2, 5}, 11));
}

TEST(CoinChangeTest, SampleTest2)
{
    EXPECT_NE(-1, coinChangeFA({2}, 3));
    EXPECT_EQ(0, coinChangeFA({2}, 3));
}

TEST(CoinChangeTest, SampleTest3)
{
    EXPECT_EQ(0, coinChangeFA({1}, 0));
}
