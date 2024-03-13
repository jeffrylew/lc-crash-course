#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <vector>

//! @brief First attempt solution to find max profit with cooldown after selling
//! @param[in] prices Vector of prices where prices[i] is price on ith day
//! @return Max profit given a cooldown where you cannot buy the next day
static int maxProfitFA(std::vector<int> prices)
{
    //! @details Space complexity O(prices.size())
    //!          Time complexity O(prices.size())

    std::vector<std::vector<int>> memo(prices.size(), std::vector<int>(2U, 0));

    std::function<int(int, int)> get_max_profit =
        [&](int curr_day, int holding_stock) -> int {
            if (curr_day >= static_cast<int>(prices.size()))
            {
                return 0;
            }

            if (memo[curr_day][holding_stock] != 0)
            {
                return memo[curr_day][holding_stock];
            }

            int max_profit {get_max_profit(curr_day + 1, holding_stock)};

            if (holding_stock == 0)
            {
                max_profit = std::max(max_profit,
                                      get_max_profit(curr_day + 1, 1)
                                      - prices[curr_day]);
            }
            else
            {
                max_profit = std::max(max_profit,
                                      get_max_profit(curr_day + 2, 0)
                                      + prices[curr_day]);
            }

            return memo[curr_day][holding_stock] = max_profit;
        };

    return get_max_profit(0, 0);
}

//! @brief Dynamic programming with state machine discussion solution
//! @param[in] prices Vector of prices where prices[i] is price on ith day
//! @return Max profit given a cooldown where you cannot buy the next day
static int maxProfitDS1(std::vector<int> prices)
{
    //! @details https://leetcode.com/problems
    //!          /best-time-to-buy-and-sell-stock-with-cooldown/editorial
    //!
    //!          Time complexity O(num_days) where num_days = prices.size().
    //!          There is one loop over the input list and the operations within
    //!          one iteration takes constant time.
    //!          Space complexity O(1), constant memory is used regardless of
    //!          the size of the input.

    /**
     *
    // Formulas to populate state arrays before optimization

    // Previous state of sold can only be hold. Thus, the max profit is max
    // profit of previous state plus revenue from selling stock
    sold[curr_day] = hold[curr_day - 1] + price[curr_day];

    // Previous state of hold could also be hold (no transaction). Or it could
    // be reset, from which one can buy stock at the current price
    hold[curr_day] = std::max(hold[curr_day - 1],
                              reset[curr_day - 1] - price[curr_day]);

    // Previous state of reset could be reset or sold. Both transitions do not
    // involve any transaction with the stock
    reset[curr_day] = std::max(reset[curr_day - 1], sold[curr_day - 1]);

    // Max profit would be std::max(sold[num_days], reset[num_days]), where we
    // either sell the stock or perform no transaction. Buying stock on the last
    // day only leads to the reduction of profits

    // Base case: Start from state reset since initially don't hold stock and
    // don't have any to sell either.
    // Assign initial values of sold[-1] and held[-1] to Integer.MIN_VALUE to
    // render paths that start from these two states impossible
     */

    int sold {std::numeric_limits<int>::min()};
    int hold {std::numeric_limits<int>::min()};
    int reset {};

    for (const int price : prices)
    {
        const int pre_sold {sold};
        sold  = hold + price;
        hold  = std::max(hold, reset - price);
        reset = std::max(reset, pre_sold);
    }

    return std::max(sold, reset);
}

//! @brief Second dynamic programming discussion solution
//! @param[in] prices Vector of prices where prices[i] is price on ith day
//! @return Max profit given a cooldown where you cannot buy the next day
static int maxProfitDS2(std::vector<int> prices)
{
    //! @details https://leetcode.com/problems
    //!          /best-time-to-buy-and-sell-stock-with-cooldown/editorial
    //!
    //!          Time complexity O(num_days ^ 2) where num_days = prices.size().
    //!          Nested loops over prices - outer loop has num_days iterations
    //!          and inner loop has 1 to num_days iterations. Thus, total number
    //!          of iterations is num_days * (num_days + 1) / 2.
    //!          Space complexity O(num_days). Allocated vector for max_profits.

    //! Base case: max_profit[num_days]. Best action with a single price is no
    //! transaction (don't lose money/gain profit) so max_profit[num_days] = 0.
    //! Initialize array with zeros for base case where min profit we gain is 0.
    //! Two additional elements prevent out of bounds for case1.
    std::vector<int> max_profit(prices.size() + 2U);

    const auto num_days = static_cast<int>(prices.size());

    //! curr_day = i in editorial diagram/explanation
    //! prev_day = i - 1 in editorial diagram/explanation
    for (int prev_day = num_days - 1; prev_day >= 0; --prev_day)
    {
        int case1 {};

        //! Case 1) Buy on prev_day and sell the stock at prices[curr_day]
        //! Profit from transaction is prices[curr_day] - prices[prev_day] plus
        //! max profits from rest of price sequence max_profit[curr_day + 2]
        for (int curr_day = prev_day + 1; curr_day < num_days; ++curr_day)
        {
            int profit {
                prices[curr_day] - prices[prev_day] + max_profit[curr_day + 2]};
            case1 = std::max(profit, case1);
        }

        //! Case 2) No transaction with the stock at prices[prev_day]
        //! Max profit would be max_profit[curr_day = prev_day + 1], which is
        //! also the max profit we can gain from the rest of the price sequence
        int case2 {max_profit[prev_day + 1]};

        //! Wrap up the two cases
        max_profit[prev_day] = std::max(case1, case2);
    }

    //! max_profit gives max profit for price subsequence starting from index i
    //! i.e. price[i, i + 1, ..., num_days]
    return max_profit[0];
}

TEST(MaxProfitTest, SampleTest1)
{
    EXPECT_EQ(3, maxProfitFA({1, 2, 3, 0, 2}));
    EXPECT_EQ(3, maxProfitDS1({1, 2, 3, 0, 2}));
    EXPECT_EQ(3, maxProfitDS2({1, 2, 3, 0, 2}));
}

TEST(MaxProfitTest, SampleTest2)
{
    EXPECT_EQ(0, maxProfitFA({1}));
    EXPECT_EQ(0, maxProfitDS1({1}));
    EXPECT_EQ(0, maxProfitDS2({1}));
}
