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

//! @brief Get Hamming distance between two ints (num positions of diff bits)
//! @param[in] x First int
//! @param[in] y Second int
//! @return Hamming distance between x and y
static int hammingDistanceDS2(int x, int y)
{
    //! @details https://leetcode.com/problems/hamming-distance/editorial/
    //!
    //!          Time complexity O(1) since the size of an integer is fixed.
    //!          However, this algorithm requires fewer iterations than the bit
    //!          shift approach in DS1.
    //!          Space complexity O(1) since a constant size of memory is used
    //!          regardless of the input.

    int x_xor_y {x ^ y};
    int hamming_distance {};

    while (x_xor_y != 0)
    {
        ++hamming_distance;

        //! Remove the rightmost bit of '1'
        x_xor_y = x_xor_y & (x_xor_y - 1);
    }

    return hamming_distance;
}

TEST(HammingDistanceTest, SampleTest1)
{
    EXPECT_EQ(2, hammingDistanceDS1(1, 4));
    EXPECT_EQ(2, hammingDistanceDS2(1, 4));
}

TEST(HammingDistanceTest, SampleTest2)
{
    EXPECT_EQ(1, hammingDistanceDS1(3, 1));
    EXPECT_EQ(1, hammingDistanceDS2(3, 1));
}
