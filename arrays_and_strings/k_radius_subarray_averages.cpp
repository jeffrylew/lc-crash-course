#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

//! @brief First attempt solution to get k-radius average for each subarray
//! @param[in] nums Vector of n integers to get k-radius averages from
//! @param[in] k    Radius of subarray spanning i - k and i + k
//! @return Vector of k-radius subarray averages
static std::vector<int> getAveragesFA(std::vector<int> nums, int k)
{
    const auto                nums_size = static_cast<int>(nums.size());
    std::vector<std::int64_t> prefixes {nums[0]};
    prefixes.reserve(nums.size());

    for (int idx = 1; idx < nums_size; ++idx)
    {
        prefixes.push_back(nums[idx] + prefixes.back());
    }

    std::vector<int> avgs(nums.size());
    for (int idx = 0; idx < nums_size; ++idx)
    {
        if (idx - k < 0 || idx + k >= nums_size)
        {
            avgs[idx] = -1;
            continue;
        }

        avgs[idx] = static_cast<int>(
            (prefixes[idx + k] - prefixes[idx - k] + nums[idx - k])
            / (2 * k + 1));
    }

    return avgs;
}

TEST(GetAveragesTest, SampleTest1)
{
    const std::vector<int> expected_output {-1, -1, -1, 5, 4, 4, -1, -1, -1};

    EXPECT_EQ(expected_output, getAveragesFA({7, 4, 3, 9, 1, 8, 5, 2, 6}, 3));
}

TEST(GetAveragesTest, SampleTest2)
{
    const std::vector<int> expected_output {100000};

    EXPECT_EQ(expected_output, getAveragesFA({100000}, 0));
}

TEST(GetAveragesTest, SampleTest3)
{
    const std::vector<int> expected_output {-1};

    EXPECT_EQ(expected_output, getAveragesFA({8}, 100000));
}
