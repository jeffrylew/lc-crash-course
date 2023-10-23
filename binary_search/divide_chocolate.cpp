#include <gtest/gtest.h>

#include <numeric>
#include <vector>

//! @brief Get max total sweetness of piece by cutting bar optimally
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessFA(std::vector<int> sweetness, int k)
{
    //! @details

    const auto sweet_size = static_cast<int>(sweetness.size());
    auto       prefix_sum = sweetness;

    for (int i = 1; i < sweet_size; ++i)
    {
        prefix_sum [i] += prefix_sum[i - 1];
    }

    //! Largest chunk size
    int largest_chunk {sweet_size - k};

    //! Keep track of maximum of minimum total sweetness
    int min_total_sweetness {};

    while (largest_chunk > 0)
    {
        int left {};
        for (int right = largest_chunk - 1; right < sweet_size; ++right)
        {
            //! @todo Think more
        }

        --largest_chunk;
    }

    return min_total_sweetness;
}

TEST(MaximizeSweetnessTest, SampleTest1)
{
    EXPECT_EQ(6, maximizeSweetnessFA({1, 2, 3, 4, 5, 6, 7, 8, 9}, 5));

    EXPECT_EQ(1, maximizeSweetnessFA({5, 6, 7, 8, 9, 1, 2, 3, 4}, 8));

    EXPECT_EQ(5, maximizeSweetnessFA({1, 2, 2, 1, 2, 2, 1, 2, 2}, 2));
}