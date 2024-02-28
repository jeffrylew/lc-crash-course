#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

//! @brief First attempt solutio to get max profit
//! @param[in] prices Vector of stock prices, prices[i] = price on ith day
//! @param[in] fee    Transaction fee
//! @return Maximum profit you can achieve
static int maxProfitFA(std::vector<int> prices, int fee)
{
    //! @todo

} // static int maxProfitFA( ...

TEST(MaxProfitTest, SampleTest1)
{
    EXPECT_EQ(8, maxProfitFA({1, 3, 2, 8, 4, 9}, 2));
}

TEST(MaxProfitTest, SampleTest2)
{
    EXPECT_EQ(6, maxProfitFA({1, 3, 7, 5, 10, 3}, 3));
}
