#include <gtest/gtest.h>

#include <stack>
#include <unordered_set>
#include <vector>

static void dfsRecursive(int                                  node,
                         std::unordered_set<int>&             seen,
                         const std::vector<std::vector<int>>& rooms)
{
    for (const int neighbor : rooms.at(node))
    {
        if (seen.emplace(neighbor).second)
        {
            dfsRecursive(neighbor, seen, rooms);
        }
    }
}

static void dfsIterative(int                                  start,
                         std::unordered_set<int>&             seen,
                         const std::vector<std::vector<int>>& rooms)
{
    std::stack<int> stack {};
    stack.emplace(start);

    while (not stack.empty())
    {
        const int node {stack.top()};
        stack.pop();

        for (const int neighbor : rooms.at(node))
        {
            if (seen.emplace(neighbor).second)
            {
                stack.push(neighbor);
            }
        }
    }
}

//! @brief Determine if all locked rooms can be visited
//! @param[in] room Adjacency list where rooms[i] is a vector of visitable rooms
//! @return True if can visit all locked rooms, else false
static bool canVisitAllRooms(const std::vector<std::vector<int>>& rooms)
{
    //! @details Time complexity is O(N + E) where N = number of rooms and
    //!          and E is the total number of keys in all rooms.
    //!          Space complexity is O(N) for seen and recursion call stack.

    std::unordered_set<int> seen {0};
    dfsRecursive(0, seen, rooms);
    // dfsIterative(0, seen, rooms);
    return seen.size() == rooms.size();
}

TEST(CanVisitAllRoomsTest, Sample1)
{
    const std::vector<std::vector<int>> room {{1}, {2}, {3}, {}};
    EXPECT_TRUE(canVisitAllRooms(rooms));
}