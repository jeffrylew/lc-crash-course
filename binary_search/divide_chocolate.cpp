#include <gtest/gtest.h>

#include <vector>

//! @brief Get max total sweetness of piece by cutting bar optimally
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessFA(std::vector<int> sweetness, int k)
{
    //! @todo
}

TEST(MaximizeSweetnessTest, SampleTest1)
{
    EXPECT_EQ(6, maximizeSweetnessFA({1, 2, 3, 4, 5, 6, 7, 8, 9}, 5));

    EXPECT_EQ(1, maximizeSweetnessFA({5, 6, 7, 8, 9, 1, 2, 3, 4}, 8));

    EXPECT_EQ(5, maximizeSweetnessFA({1, 2, 2, 1, 2, 2, 1, 2, 2}, 2));
}