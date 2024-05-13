#include <gtest/gtest.h>

//! @brief Get Hamming distance between two ints (num positions of diff bits)
//! @param[in] x First int
//! @param[in] y Second int
//! @return Hamming distance between x and y
static int hammingDistanceFA(int x, int y)
{
    //! @todo
}

TEST(HammingDistanceTest, SampleTest1)
{
    EXPECT_EQ(2, hammingDistanceFA(1, 4));
}

TEST(HammingDistanceTest, SampleTest2)
{
    EXPECT_EQ(1, hammingDistanceFA(3, 1));
}
