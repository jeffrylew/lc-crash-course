#include <gtest/gtest.h>

#include <stack>
#include <utility>

class StockSpanner
{
    //! Monotonic decreasing stack of [priceTop, answerTop]
    std::stack<std::pair<int, int>> stack {};

    public:
        StockSpanner() {}

        //! @brief Get span of stock's price for current day
        //! @param[in] price Price of stock for current day
        //! @return Max number of consecutive days where price <= current day's
        int next(int price)
        {
            //! @details https://leetcode.com/problems/online-stock-span/
            //!          editorial/
            //!
            //!          Time complexity O(1), even though there is a while loop
            //!          in next it can only run N (= # of calls to next) times
            //!          across the entire algorithm. Each element can only be
            //!          popped off the stack once and there are up to N.
            //!          Space complexity O(N) - in the worst case scenario when
            //!          all stock prices are decreasing the while loop never
            //!          runs so stack grows to size of N.

            int ans {1};

            while (not stack.empty() && stack.top().first <= price)
            {
                ans += stack.top().second;
                stack.pop();
            }

            stack.emplace(price, ans);
            return ans;
        }
};

TEST(StockSpannerTest, SampleTest)
{
    StockSpanner obj {};

    EXPECT_EQ(1, obj.next(100));
    EXPECT_EQ(1, obj.next(80));
    EXPECT_EQ(1, obj.next(60));
    EXPECT_EQ(2, obj.next(70));
    EXPECT_EQ(1, obj.next(60));
    EXPECT_EQ(4, obj.next(75));
    EXPECT_EQ(6, obj.next(85));
}