#include <gtest/gtest.h>

#include <queue>

class MovingAverage
{
    int    window_size {};
    double window_sum {};

    std::queue<int> window {};

    public:
        MovingAverage(int size) : window_size {size} {}

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
};

TEST(MovingAverageTest, TestNext)
{
    MovingAverage avg(3);

    EXPECT_DOUBLE_EQ(1.0, avg.nextFA(1));
    EXPECT_DOUBLE_EQ(5.5, avg.nextFA(10));
    EXPECT_NEAR(4.66667, avg.nextFA(3));
    EXPECT_DOUBLE_EQ(6.0, avg.nextFA(5));
}