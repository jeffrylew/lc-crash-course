#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief Get max profit with at most k transactions
//! @param[in] k Number of transactions
//! @param[in] prices Vector of stock prices where prices[i] is price on ith day
//! @return Max profit can achieve with at most k transactions
static int maxProfitDS1(int k, std::vector<int> prices)
{
    //! @details https://leetcode.com/problems
    //!          /best-time-to-buy-and-sell-stock-iv/description/
    //!
    //!          Time complexity: O(N * K) where N = prices.size() AKA number of
    //!          days and K = number of transactions. Work done at each state is
    //!          O(1) so time complexity is number of states - holding_stock
    //!          contribution is constant.
    //!          Space complexity: O(N * K)

    //! <current day, currently holding stock or not, remaining transactions>
    std::vector<std::vector<std::vector<int>>> memo(
        prices.size(), std::vector(2, std::vector(k + 1, -1)));

    //! curr_day:      Current day
    //! holding_stock: Bool representing if holding stock. 0 = false, 1 = true
    //! remain_tx:     Number of transactions remaining
    std::function<int(int, int, int)> get_max_profit =
        [&](int curr_day, int holding_stock, int remain_tx) {
            //! Base case: Reached end of input or ran out of transactions
            //!            Cannot make any more transactions
            if (curr_day == static_cast<int>(prices.size()) || remain_tx == 0)
            {
                return 0;
            }

            if (memo[curr_day][holding_stock][remain_tx] != -1)
            {
                return memo[curr_day][holding_stock][remain_tx];
            }

            //! Three decisions at each state:
            //! - If not holding stock, can buy or skip
            //! - If holding stock, can sell or skip
            //!
            //! get_max_profit(curr_day, holding_stock, remain_tx)
            //!   = max(skip, buy, sell)
            //! where
            //!   skip = get_max_profit(curr_day + 1, holding_stock, remain_tx)
            //!   buy  = get_max_profit(curr_day + 1, 1, remain_tx)
            //!          - prices[curr_day]
            //!   sell = get_max_profit(curr_day + 1, 0, remain_tx - 1)
            //!          + prices[curr_day]

            //! Initialize with skip case profit: Move to next day
            int max_profit {
                get_max_profit(curr_day + 1, holding_stock, remain_tx)};

            if (holding_stock == 1)
            {
                //! If holding stock, get max between skip and sell cases
                //! Sell profit: get_max_profit(curr_day + 1, 0, remain_tx - 1)
                //!              + prices[curr_day]
                //! - Gain prices[curr_day]
                //! - Move to next day (curr_day + 1)
                //! - No longer holding stock (0 = false)
                //! - Used one transaction (remain_tx - 1)
                max_profit =
                    std::max(max_profit,
                             get_max_profit(curr_day + 1, 0, remain_tx - 1)
                             + prices[curr_day]);
            }
            else
            {
                //! If not holding stock, get max between skip and buy cases
                //! Buy profit: get_max_profit(curr_day + 1, 1, remain_tx)
                //!             - prices[curr_day]
                //! - Spend prices[curr_day] to buy stock
                //! - Move to next day (curr_day + 1)
                //! - Now holding stock (1 = true)
                //! - Haven't completed transaction yet so remain_tx stays same
                max_profit =
                    std::max(max_profit,
                             get_max_profit(curr_day + 1, 1, remain_tx)
                             - prices[curr_day]);
            }

            return memo[curr_day][holding_stock][remain_tx] = max_profit;
        };

    //! Max profit starting on day 0, not holding stock, k transactions remain
    return get_max_profit(0, 0, k);

} // static int maxProfitDS1( ...

TEST(MaxProfitTest, SampleTest1)
{
    EXPECT_EQ(2, maxProfitDS1(2, {2, 4, 1}));
}

TEST(MaxProfitTest, SampleTest2)
{
    EXPECT_EQ(7, maxProfitDS1(2, {3, 2, 6, 5, 0, 3}));
}
