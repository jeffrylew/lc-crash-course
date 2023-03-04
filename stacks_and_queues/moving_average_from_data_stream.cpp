#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <queue>

class MovingAverage
{
    int    window_size {};
    double window_sum {};

    int size_DS1 {};
    int window_sum_DS1 {};
    int count_DS1 {};

    std::queue<int> window {};

    std::deque<int> deque_DS1 {};

    public:
        MovingAverage(int size)
            : window_size {size}
            , size_DS1 {size}
        {
        }

        //! @brief First attempt to get moving average of last size values
        //! @param[in] val Next value in stream
        //! @return Moving average of size values as a double
        double nextFA(int val)
        {
            window.push(val);
            window_sum += static_cast<double>(val);

            while (static_cast<int>(window.size()) > window_size)
            {
                window_sum -= static_cast<double>(window.front());
                window.pop();
            }

            return window_sum / static_cast<double>(window.size());
        }

        //! @brief Double-ended queue LC discussion solution
        //! @param[in] val Next integer in stream
        //! @return Moving average of size values as a double
        double nextDS1(int val)
        {
            //! @details https://leetcode.com/problems/
            //!          moving-average-from-data-stream/editorial/
            //!
            //!          Time complexity O(1)
            //!          Space complexity O(N) where N is size of moving window

            int tail {};
            deque_DS1.push_back(val);

            if (++count > size_DS1)
            {
                tail = deque_DS1.front();
                deque_DS1.pop_front();
            }

            window_sum_DS1 = window_sum_DS1 - tail + val;

            return window_sum_DS1 * 1.0 / std::min(size_DS1, count);
        }
};

TEST(MovingAverageTest, TestNext)
{
    MovingAverage avg(3);

    EXPECT_DOUBLE_EQ(1.0, avg.nextFA(1));
    EXPECT_DOUBLE_EQ(5.5, avg.nextFA(10));
    EXPECT_NEAR(4.66667, avg.nextFA(3));
    EXPECT_DOUBLE_EQ(6.0, avg.nextFA(5));

    EXPECT_DOUBLE_EQ(1.0, avg.nextDS1(1));
    EXPECT_DOUBLE_EQ(5.5, avg.nextDS1(10));
    EXPECT_NEAR(4.66667, avg.nextDS1(3));
    EXPECT_DOUBLE_EQ(6.0, avg.nextDS1(5));
}