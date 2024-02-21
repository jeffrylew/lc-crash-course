#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get max total value of coins if choose exactly k coins optimally
//! @param[in] piles Vector of pile compositions, where piles[i] = ith pile comp
//! @param[in] k     Positive integer representing number of coins to choose
//! @return Max total value of coins in wallet if choose exactly k optimally
static int maxValueOfCoinsDS1(const std::vector<std::vector<int>>& piles, int k)
{
    //! @details https://leetcode.com/problems
    //!          /maximum-value-of-k-coins-from-piles/description/
    //!
    //!          Time complexity O(N * k * x) where N = piles.size() = number of
    //!          piles and k = num coins to choose. There are O(N * k) states.
    //!          Assume the avg number of coins per pile is x = piles[i].size()
    //!          and at each state we have a for loop that iterates x times.
    //!          Space complexity O(N * k)

    std::vector<std::vector<int>> memo(
        piles.size(), std::vector(k + 1, -1));

    //! curr_pile:    current pile we are on
    //! remain_coins: how many more coins we can take
    //! get_max_value(curr_pile, remain_coins) returns max value of coins we can
    //! take starting from curr_pile with remain_coins moves remaining
    std::function<int(int, int)> get_max_value =
        [&](int curr_pile, int remain_coins) -> int {
            if (curr_pile == static_cast<int>(piles.size())
                || remain_coins == 0)
            {
                //! Base case: Either reached end of input (no piles left) or
                //!            remain_coins = 0 (can't take any more coins).
                //!            Max value we can achieve is 0.
                return 0;
            }

            if (memo[curr_pile][remain_coins] != -1)
            {
                return memo[curr_pile][remain_coins];
            }

            //! Skip this pile
            int max_value {get_max_value(curr_pile + 1, remain_coins)};

            int        curr_value {};
            const auto pile_size = static_cast<int>(piles[curr_pile].size());

            //! If don't skip pile, can take up to "coin" coins
            for (int coin = 0; coin < std::min(remain_coins, pile_size); ++coin)
            {
                //! curr_value tracks value of coins taken from current pile
                curr_value += piles[curr_pile][coin];
                max_value =
                    std::max(max_value,
                             get_max_value(curr_pile + 1,
                                           remain_coins - coin - 1)
                             + curr_value);
            }

            return memo[curr_pile][remain_coins] = max_value;
        };

    return get_max_value(0, k);

} // static int maxValueOfCoinsDS1( ...

//! @brief Bottom up dynamic programming solution
//! @param[in] piles Vector of pile compositions, where piles[i] = ith pile comp
//! @param[in] k     Positive integer representing number of coins to choose
//! @return Max total value of coins in wallet if choose exactly k optimally
static int maxValueOfCoinsDS2(const std::vector<std::vector<int>>& piles, int k)
{
    //! @details https://leetcode.com/problems
    //!          /maximum-value-of-k-coins-from-piles/description/
    //!
    //!          Time complexity O(N * k * x) where N = piles.size() = number of
    //!          piles and k = num coins to choose. There are O(N * k) states.
    //!          Assume the avg number of coins per pile is x = piles[i].size()
    //!          and at each state we have a for loop that iterates x times.
    //!          Space complexity O(N * k)

    const auto num_piles = static_cast<int>(piles.size());

    std::vector<std::vector<int>> dp(num_piles + 1, std::vector(k + 1, 0));

    for (int curr_pile = num_piles - 1; curr_pile >= 0; --curr_pile)
    {
        for (int remain_coins = 1; remain_coins <= k; ++remain_coins)
        {
            //! Skip this pile
            dp[curr_pile][remain_coins] = dp[curr_pile + 1][remain_coins];
            int curr_value {};

            const auto pile_size = static_cast<int>(piles[curr_pile].size());
            for (int coin = 0; coin < std::min(remain_coins, pile_size); ++coin)
            {
                curr_value += piles[curr_pile][coin];
                dp[curr_pile][remain_coins] =
                    std::max(dp[curr_pile][remain_coins],
                             dp[curr_pile + 1][remain_coins - coin - 1]
                             + curr_value);
            }
        }
    }

    return dp[0][k];

} // static int maxValueOfCoinsDS2( ...

TEST(MaxValueOfCoinsTest, SampleTest1)
{
    const std::vector<std::vector<int>> piles {{1, 100, 3}, {7, 8, 9}};

    EXPECT_EQ(101, maxValueOfCoinsDS1(piles, 2));
    EXPECT_EQ(101, maxValueOfCoinsDS2(piles, 2));
}

TEST(MaxValueOfCoinsTest, SampleTest2)
{
    const std::vector<std::vector<int>> piles {
        {100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}};

    EXPECT_EQ(706, maxValueOfCoinsDS1(piles, 7));
    EXPECT_EQ(706, maxValueOfCoinsDS2(piles, 7));
}
