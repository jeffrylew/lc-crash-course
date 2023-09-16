#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief First attempt to get max subseq len from nums where sum <= queries[i]
//! @param[in] nums    Vector of ints (size N) to take subsequences from
//! @param[in] queries Vector of ints (size M), queries[i] = max subsequence sum
//! @return Vector of ints (size M) containing subsequence sizes
static std::vector<int> answerQueriesFA(
    std::vector<int> nums, std::vector<int> queries)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /710/binary-search/4574/
    //!
    //!          Time complexity O(N * M + N * log N)
    //!          Space complexity O(M)

    std::vector<int> seq_sizes {};
    seq_sizes.reserve(queries.size()); // O(M)

    std::sort(nums.begin(), nums.end()); // O(N * log N)

    const auto nums_size = static_cast<int>(nums.size());

    for (const int query : queries)
    {
        int sum {};
        int idx {};

        while (idx < nums_size) // Worst case O(N * M)
        {
            if (sum + nums[idx] > query)
            {
                break;
            }

            sum += nums[idx++];
        }

        seq_sizes.push_back(idx);
    }

    return seq_sizes;
    
} // static std::vector<int> answerQueriesFA( ...

TEST(AnswerQueriesTest, SampleTest1)
{
    const std::vector<int> nums {4, 5, 2, 1};
    const std::vector<int> queries {3, 10, 21};
    const std::vector<int> expected_output {2, 3, 4};

    EXPECT_EQ(expected_output, answerQueriesFA(nums, queries));
}

TEST(AnswerQueriesTest, SampleTest2)
{
    const std::vector<int> nums {2, 3, 4, 5};
    const std::vector<int> queries {1};
    const std::vector<int> expected_output {0};

    EXPECT_EQ(expected_output, answerQueriesFA(nums, queries));
}