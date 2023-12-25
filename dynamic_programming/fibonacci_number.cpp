#include <gtest/gtest.h>

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

TEST(FibonacciTest, SampleTest1)
{
    EXPECT_EQ(0, fibonacci1(0));
}

TEST(FibonacciTest, SampleTest2)
{
    EXPECT_EQ(1, fibonacci1(1));
}
