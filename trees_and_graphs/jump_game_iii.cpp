#include <gtest/gtest.h>

#include <queue>
#include <vector>

//! @brief First attempt solution to check if can reach any index with value 0
//! @param[in] arr   Vector of non-negative integers
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

//! @brief BFS solution to check if can reach any index with value 0
//! @param[in] arr   Vector of non-negative integers
//! @param[in] start Initial index in arr
//! @return True if can reach any index with value 0, else false
static bool canReachBFS(std::vector<int> arr, int start)
{
    //! @details https://leetcode.com/problems/jump-game-iii/editorial/
    //!
    //!          Time complexity O(N) where N = arr.size(). We visit every index
    //!          at most once.
    //!          Space complexity O(N) since need queue to store next index.
    //!          queue keeps at most two levels of nodes and each node has two
    //!          childeren at most. Traversal of this solution is a binary tree.
    //!          Max number of nodes in a single level would be N / 2 so the max
    //!          length of queue is O(N / 2) + O(N / 2) = O(N)

    const auto n = static_cast<int>(arr.size());

    std::queue<int> queue({start});

    while (not queue.empty())
    {
        const int node {queue.front()};
        queue.pop();

        //! Check if we reached zero
        if (arr.at(node) == 0)
        {
            return true;
        }

        if (arr.at(node) > 0)
        {
            //! Check available next steps
            if (node + arr.at(node) < n)
            {
                queue.push(node + arr.at(node));
            }

            if (node - arr.at(node) >= 0)
            {
                queue.push(node - arr.at(node));
            }

            //! Mark as visited
            arr[node] = -arr[node];
        }
    }

    return false;
}

TEST(CanReachTest, SampleTest)
{
    EXPECT_TRUE(canReachFA({4, 2, 3, 0, 3, 1, 2}, 5));

    EXPECT_TRUE(canReachFA({4, 2, 3, 0, 3, 1, 2}, 0));

    EXPECT_FALSE(canReachFA({3, 0, 2, 1, 2}, 2));
}