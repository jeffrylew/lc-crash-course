#include <gtest/gtest.h>

#include <queue>
#include <utility>
#include <vector>

//! @brief First attempt solution to get k closest points to origin (0, 0)
//! @param[in] points Reference to vector of points[i] = [x_i, y_i]
//! @param[in] k      Number of closest points to retrieve
//! @return Vector of k closest points to origin
std::vector<std::vector<int>> kClosestFA(
    const std::vector<std::vector<int>>& points, int k)
{
    //! @details Time complexity O(N * log k) where N = points.size(). For each
    //!          point in input, need to push/pop to a heap of size k. Each
    //!          operation takes O(log k).
    //!          Space complexity O(k) for heap. O(N) for output (excluded).
    
    std::priority_queue<std::pair<int, std::vector<int>>> maxHeap {};

    for (const auto& point : points)
    {
        maxHeap.emplace(point[0] * point[0] + point[1] * point[1], point);

        if (static_cast<int>(maxHeap.size()) > k)
        {
            maxHeap.pop();
        }
    }

    std::vector<std::vector<int>> output {};
    output.reserve(k);

    while (not maxHeap.empty())
    {
        output.emplace_back(maxHeap.top().second);
        maxHeap.pop();
    }

    return output;
}

TEST(KClosestTest, SampleTest1)
{
    const std::vector<std::vector<int>> points {{1, 3}, {-2, 2}};
    const std::vector<std::vector<int>> expected_output {{-2, 2}};

    EXPECT_EQ(expected_output, kClosestFA(points, 1));
}

TEST(KClosestTest, SampleTest2)
{
    const std::vector<std::vector<int>> points {{3, 3}, {5, -1}, {-2, 4}};
    const std::vector<std::vector<int>> expected_output {{3, 3}, {-2, 4}};

    EXPECT_EQ(expected_output, kClosestFA(points, 2));
}