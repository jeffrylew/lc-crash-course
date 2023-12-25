#include <gtest/gtest.h>

#include <functional>
#include <unordered_map>

static int fibonacci1(int n)
{
    //! @details Time complexity O(2 ^ n) since each call creates 2 more calls
    //!          Space complexity O(1)

    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return fibonacci1(n - 1) + fibonacci1(n - 2);
}

static int fibonacci2(int n)
{
    //! @details Time complexity O(n) by memoizing results
    //!          Space complexity O(1)

    std::unordered_map<int, int> memo {};

    std::function<int(int)> fibonacci = [&](int num) -> int {
        if (num == 0)
        {
            return 0;
        }

        if (num == 1)
        {
            return 1;
        }

        if (memo.find(num) != memo.end())
        {
            return memo[num];
        }

        return memo[num] = fibonacci(num - 1) + fibonacci(num - 2);
    };

    return fibonacci(n);
}

TEST(FibonacciTest, SampleTest1)
{
    EXPECT_EQ(0, fibonacci1(0));
    EXPECT_EQ(0, fibonacci2(0));
}

TEST(FibonacciTest, SampleTest2)
{
    EXPECT_EQ(1, fibonacci1(1));
    EXPECT_EQ(1, fibonacci2(1));
}
