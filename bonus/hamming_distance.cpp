#include <gtest/gtest.h>

//! @brief Get Hamming distance between two ints (num positions of diff bits)
//! @param[in] x First int
//! @param[in] y Second int
//! @return Hamming distance between x and y
static int hammingDistanceDS1(int x, int y)
{
    //! @details https://leetcode.com/problems/hamming-distance/editorial/
    //!
    //!          Time complexity O(1) since int has fixed size. 32 bit integer
    //!          would take at most 32 iterations.
    //!          Space complexity O(1) since a constant size of memory is used
    //!          regardless of the input.

    int x_xor_y {x ^ y};
    int hamming_distance {};

    while (x_xor_y != 0)
    {
        if (x_xor_y % 2 == 1)
        {
            ++hamming_distance;
        }

        x_xor_y = x_xor_y >> 1;
    }

    return hamming_distance;
}

TEST(HammingDistanceTest, SampleTest1)
{
    EXPECT_EQ(2, hammingDistanceDS1(1, 4));
}

TEST(HammingDistanceTest, SampleTest2)
{
    EXPECT_EQ(1, hammingDistanceDS1(3, 1));
}
