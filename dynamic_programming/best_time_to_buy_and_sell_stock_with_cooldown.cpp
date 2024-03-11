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

static int maxProfitDS1(std::vector<int> prices)
{
    int sold {std::numeric_limits<int>::min()};
    int hold {std::numeric_limits<int>::min()};
    int reset {};

    for (const int price : prices)
    {
        const int pre_sold {sold};
        sold  = held + price;
        held  = std::max(held, reset - price);
        reset = std::max(reset, pre_sold);
    }

    return std::max(sold, reset);
}

TEST(MaxProfitTest, SampleTest1)
{
    EXPECT_EQ(3, maxProfitFA({1, 2, 3, 0, 2}));
    EXPECT_EQ(3, maxProfitDS1({1, 2, 3, 0, 2}));
}

TEST(MaxProfitTest, SampleTest2)
{
    EXPECT_EQ(0, maxProfitFA({1}));
    EXPECT_EQ(0, maxProfitDS1({1}));
}
