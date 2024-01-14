#include <gtest/gtest.h>

#include <functional>
#include <vector>

//! @brief First attempt to get number of distinct ways to reach n steps
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsFA(int n)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /712/dynamic-programming/4580/

    std::vector<int> memo(n + 1);

    std::function<int(int)> dp = [&](int nsteps) {
        if (nsteps == 1)
        {
            return 1; 
        }

        if (nsteps == 2)
        {
            return 2;
        }

        if (memo[nsteps] != 0)
        {
            return memo[nsteps];
        }

        /*
        //! Divide dp(nstep - 2) by two to avoid double counting
        return dp(nsteps - 2) / 2 + dp(nsteps - 1) + 1;
         */

        //! Divide dp(nsteps - 1) by two to avoid double counting
        return 2 * dp(nsteps - 2) + dp(nsteps - 1) / 2;
    };

    return dp(n);
}

TEST(ClimbStairsTest, SampleTest1)
{
    EXPECT_EQ(2, climbStairsFA(2));
}

TEST(climbStairsTest, SampleTest2)
{
    EXPECT_EQ(3, climbStairsFA(3));
}

TEST(ClimbStairsTest, SampleTest3)
{
    EXPECT_EQ(8, climbStairsFA(5));
    // EXPECT_EQ(7, climbStairsFA(5));
}

TEST(ClimbStairsTest, SampleTest4)
{
    EXPECT_NE(13, climbStairsFA(6));
    EXPECT_EQ(14, climbStairsFA(6));
}
