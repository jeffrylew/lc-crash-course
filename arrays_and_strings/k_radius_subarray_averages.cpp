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

//! @brief Prefix sum discussion solution to get k-radius averages
//! @param[in] nums Vector of n integers to get k-radius averages from
//! @param[in] k    Radius of subarray spanning i - k and i + k
//! @return Vector of k-radius subarray averages
static std::vector<int> getAveragesDS1(std::vector<int> nums, int k)
{
    //! @details https://leetcode.com/problems/k-radius-subarray-averages
    //!
    //!          Time complexity O(n) where n = nums.size(). Generating the
    //!          prefix vector takes O(n) to iterate over nums once. Iterating
    //!          over nums to fill the averages vector takes O(n) since finding
    //!          the average of each index is a constant time operation.
    //!          Space complexity O(n). The output vector averages is not
    //!          considered additional space but use prefix vector of size n + 1

    //! When a single element is considered then its average is the num itself
    if (k == 0)
    {
        return nums;
    }

    const int        window_size {2 * k + 1};
    const auto       nums_size = static_cast<int>(nums.size());
    std::vector<int> averages(nums.size(), -1);

    //! Case when any index does not have k elements on either side
    if (window_size > nums_size)
    {
        return averages;
    }

    //! Generate prefix vector for nums
    //! prefix[idx + 1] is the sum of all elements from index 0 to idx
    std::vector<long long> prefix(nums.size() + 1U);
    for (int idx = 0; idx < nums_size; ++idx)
    {
        prefix[idx + 1] = prefix[idx] + nums[idx];
    }

    //! Only iterate on indices that have at least k elements on either side
    //! i.e. Indices from k (inclusive) to nums_size - k (exclusive)
    for (int idx = k; idx < (nums_size - k); ++idx)
    {
        const int left_bound {idx - k};
        const int right_bound {idx + k};

        const long long subarray_sum {
            prefix[right_bound + 1] - prefix[left_bound]};
        averages[idx] = static_cast<int>(subarray_sum / window_size);
    }

    return averages;

} // static std::vector<int> getAveragesDS1( ...

TEST(GetAveragesTest, SampleTest1)
{
    const std::vector<int> expected_output {-1, -1, -1, 5, 4, 4, -1, -1, -1};

    EXPECT_EQ(expected_output, getAveragesFA({7, 4, 3, 9, 1, 8, 5, 2, 6}, 3));
    EXPECT_EQ(expected_output, getAveragesDS1({7, 4, 3, 9, 1, 8, 5, 2, 6}, 3));
}

TEST(GetAveragesTest, SampleTest2)
{
    const std::vector<int> expected_output {100000};

    EXPECT_EQ(expected_output, getAveragesFA({100000}, 0));
    EXPECT_EQ(expected_output, getAveragesDS1({100000}, 0));
}

TEST(GetAveragesTest, SampleTest3)
{
    const std::vector<int> expected_output {-1};

    EXPECT_EQ(expected_output, getAveragesFA({8}, 100000));
    EXPECT_EQ(expected_output, getAveragesDS1({8}, 100000));
}
