#include <gtest/gtest.h>

#include <cmath>
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

//! @brief Brute force solution to get number of distinct ways to reach n steps
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsDS1(int n)
{
    //! @details https://leetcode.com/problems/climbing-stairs/editorial/
    //!
    //!          Time complexity O(2 ^ n), size of recursion tree is 2 ^ n.
    //!          Space complexity O(n), the depth of the recursion tree can go
    //!          up to n.

    std::function<int(int)> dp = [](int curr_step) -> int {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        return dp(curr_step + 1) + dp(curr_step + 2);
    };

    return dp(0);
}

//! @brief Recursion with memoization solution
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsDS2(int n)
{
    //! @details https://leetcode.com/problems/climbing-stairs/editorial/
    //!
    //!          Time complexity O(n), size of recursion tree can go up to n.
    //!          Space complexity O(n), the depth of the recursion tree can go
    //!          up to n.

    std:vector<int> memo(n + 1);

    std::function<int(int)> dp = [&](int curr_step) -> int {
        if (curr_step > n)
        {
            return 0;
        }

        if (curr_step == n)
        {
            return 1;
        }

        if (memo[curr_step] > 0)
        {
            return memo[curr_step];
        }

        return memo[curr_step] = dp(curr_step + 1) + dp(curr_step + 2);
    };

    return dp(0);
}

//! @brief Bottom up dynamic programming solution
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsDS3(int n)
{
    //! @details https://leetcode.com/problems/climbing-stairs/editorial/
    //!
    //!          Time complexity O(n), single loop can go up to n.
    //!          Space complexity O(n), dp vector of size n is used.

    if (n == 1)
    {
        return 1;
    }

    std::vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;

    for (int curr_step = 3; curr_step <= n; ++curr_step)
    {
        dp[curr_step] = dp[curr_step - 1] + dp[curr_step - 2];
    }

    return dp[n];
}

//! @brief Fibonacci number solution
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsDS4(int n)
{
    //! @details https://leetcode.com/problems/climbing-stairs/editorial/
    //!
    //!          Time complexity O(n), single loop up to n for nth Fibonacci num
    //!          Space complexity O(1)

    if (n == 1)
    {
        return 1;
    }

    int first {1};
    int second {2};

    for (int curr_step = 3; curr_step <= n; ++curr_step)
    {
        const int third {first + second};
        first  = second;
        second = third;
    }

    return second;
}

//! @brief Binet's Formula solution, skip Binet's Method using matrices
//! @param[in] n Number of steps to reach the top, can climb 1 or 2 steps
//! @return Number of distinct ways can climb to the top
static int climbStairsDS5(int n)
{
    //! @details https://leetcode.com/problems/climbing-stairs/editorial/
    //!
    //!          Time complexity O(1), editorial says Java's pow method takes
    //!          log n time but in C++ std::pow is O(1) 
    //!          Space complexity O(1)

    const double sqrt5 {std::sqrt(5.0)};
    const double phi {(1.0 + sqrt5) / 2.0};
    const double psi {(1.0 - sqrt5) / 2.0};
    return static_cast<int>(
        (std::pow(phi, n + 1.0) - std::pow(psi, n + 1.0)) / sqrt5);
}

TEST(ClimbStairsTest, SampleTest1)
{
    EXPECT_EQ(2, climbStairsFA(2));
    EXPECT_EQ(2, climbStairsDS1(2));
    EXPECT_EQ(2, climbStairsDS2(2));
    EXPECT_EQ(2, climbStairsDS3(2));
    EXPECT_EQ(2, climbStairsDS4(2));
    EXPECT_EQ(2, climbStairsDS5(2));
}

TEST(climbStairsTest, SampleTest2)
{
    EXPECT_EQ(3, climbStairsFA(3));
    EXPECT_EQ(3, climbStairsDS1(3));
    EXPECT_EQ(3, climbStairsDS2(3));
    EXPECT_EQ(3, climbStairsDS3(3));
    EXPECT_EQ(3, climbStairsDS4(3));
    EXPECT_EQ(3, climbStairsDS5(3));
}

TEST(ClimbStairsTest, SampleTest3)
{
    EXPECT_EQ(8, climbStairsFA(5));
    // EXPECT_EQ(7, climbStairsFA(5));
    EXPECT_EQ(8, climbStairsDS1(5));
    EXPECT_EQ(8, climbStairsDS2(5));
    EXPECT_EQ(8, climbStairsDS3(5));
    EXPECT_EQ(8, climbStairsDS4(5));
    EXPECT_EQ(8, climbStairsDS5(5));
}

TEST(ClimbStairsTest, SampleTest4)
{
    EXPECT_NE(13, climbStairsFA(6));
    EXPECT_EQ(14, climbStairsFA(6));
    EXPECT_EQ(13, climbStairsDS1(6));
    EXPECT_EQ(13, climbStairsDS2(6));
    EXPECT_EQ(13, climbStairsDS3(6));
    EXPECT_EQ(13, climbStairsDS4(6));
    EXPECT_EQ(13, climbStairsDS5(6));
}
