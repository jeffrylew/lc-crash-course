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

//! @brief Brute force solution to get fewest number of coins to create amount
//! @param[in] coins Vector of coins of different denominations
//! @param[in] amount Target total amount of money
//! @return Fewest number of coins to make amount or -1 if cannot create amount
static int coinChangeDS1(std::vector<int> coins, int amount)
{
    //! @details https://leetcode.com/problems/coin-change/editorial/
    //!
    //!          Time complexity O(S ^ N) where S = amount and N = coins.size(),
    //!          which is the number of denominations. For each amount in [0, S]
    //!          there are N denominations that can be chosen.
    //!          Space complexity O(S) for the recursion stack

    std::function<int(int)> get_min_coins = [&](int remaining_amt) {
        if (remaining_amt < 0)
        {
            return -1;
        }

        if (remaining_amt == 0)
        {
            return 0;
        }

        //! Initialize to a large value. Smallest denomination is 1 so there can
        //! be a maximum of amount coins. amount + 1 serves as the large value.
        int min_count {amount + 1};

        for (const int coin : coins)
        {
            const int count {get_min_coins(remaining_amt - coin)};

            if (count == -1)
            {
                continue;
            }

            min_count = std::min(min_count, count + 1);
        }

        return min_count == (amount + 1) ? -1 : min_count;
    };

    return get_min_coins(amount);

} // static int coinChangeDS1( ...

TEST(CoinChangeTest, SampleTest1)
{
    EXPECT_EQ(3, coinChangeFA({1, 2, 5}, 11));
    EXPECT_EQ(3, coinChangeDS1({1, 2, 5}, 11));
}

TEST(CoinChangeTest, SampleTest2)
{
    EXPECT_NE(-1, coinChangeFA({2}, 3));
    EXPECT_EQ(0, coinChangeFA({2}, 3));
    EXPECT_EQ(-1, coinChangeDS1({2}, 3));
}

TEST(CoinChangeTest, SampleTest3)
{
    EXPECT_EQ(0, coinChangeFA({1}, 0));
    EXPECT_EQ(0, coinChangeDS1({1}, 0));
}
