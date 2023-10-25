#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <numeric>
#include <vector>

//! @brief Get max total sweetness of piece by cutting bar optimally
//! @param[in] sweetness Vector of sweetness in chocolate
//! @param[in] k         Number of cuts to chocolate bar
//! @return Max total sweetness of piece with minimum total sweetness
static int maximizeSweetnessFA(std::vector<int> sweetness, int k)
{
    //! @details This solution is incorrect

    const auto sweet_size = static_cast<int>(sweetness.size());
    auto       prefix_sum = sweetness;

    for (int i = 1; i < sweet_size; ++i)
    {
        prefix_sum [i] += prefix_sum[i - 1];
    }

    //! Largest chunk size
    int largest_chunk {sweet_size - k};

    //! Keep track of maximum of minimum total sweetness
    int min_total_sweetness {std::numeric_limits<int>::max()};

    while (largest_chunk > 0)
    {
        int left {};
        for (int right = largest_chunk; right < sweet_size; ++right)
        {
            min_total_sweetness =
                std::min(min_total_sweetness,
                         std::accumulate(prefix_sum.begin() + left,
                                         prefix_sum.begin() + right,
                                         0));
            ++left;
        }

        --largest_chunk;
        left = 0;
    }

    return min_total_sweetness;
}

TEST(MaximizeSweetnessTest, SampleTest1)
{
    EXPECT_NE(6, maximizeSweetnessFA({1, 2, 3, 4, 5, 6, 7, 8, 9}, 5));

    EXPECT_EQ(1, maximizeSweetnessFA({5, 6, 7, 8, 9, 1, 2, 3, 4}, 8));

    EXPECT_NE(5, maximizeSweetnessFA({1, 2, 2, 1, 2, 2, 1, 2, 2}, 2));
}