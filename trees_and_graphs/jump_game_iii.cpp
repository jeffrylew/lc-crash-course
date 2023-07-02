#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief First attempt solution to check if can reach any index with value 0
//! @param[in] arr Vector of non-negative integers
//! @param[in] start Initial index in arr
//! @return True if can reach any index with value 0, else false
static bool canReachFA(std::vector<int> arr, int start)
{
    std::queue<int>   queue({start});
    std::vector<bool> seen(arr.size());
    seen[start] = true;

    while (not queue.empty())
    {
        const auto idx = queue.front();
        queue.pop();

        if (arr.at(idx) == 0)
        {
            return true;
        }

        const int minus {idx - arr.at(idx)};
        if (minus >= 0 && not seen[minus])
        {
            queue.push(minus);
            seen[minus] = true;
        }

        const int plus {idx + arr.at(idx)};
        if (plus < static_cast<int>(arr.size()) && not seen[plus])
        {
            queue.push(plus);
            seen[plus] = true;
        }
    }

    return false;

} // static bool canReachFA( ...

TEST(CanReachTest, SampleTest)
{
    EXPECT_TRUE(canReachFA({4, 2, 3, 0, 3, 1, 2}, 5));

    EXPECT_TRUE(canReachFA({4, 2, 3, 0, 3, 1, 2}, 0));

    EXPECT_FALSE(canReachFA({3, 0, 2, 1, 2}, 2));
}