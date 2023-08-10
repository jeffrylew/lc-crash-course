#include <gtest/gtest.h>

#include <algorithm>
#include <cstdint>
#include <queue>
#include <random>
#include <utility>
#include <vector>

//! @brief First attempt solution to get k closest points to origin (0, 0)
//! @param[in] points Reference to vector of points[i] = [x_i, y_i]
//! @param[in] k      Number of closest points to retrieve
//! @return Vector of k closest points to origin
static std::vector<std::vector<int>> kClosestFA(
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

//! @brief Discussion solution: Sort
//! @param[in] points Reference to vector of points[i] = [x_i, y_i]
//! @param[in] k      Number of closest points to retrieve
//! @return Vector of k closest points to origin
static std::vector<std::vector<int>> kClosestDS1(
    const std::vector<std::vector<int>>& points, int k)
{
    //! @details leetcode.com/problems/k-closest-points-to-origin/editorial
    //!
    //!          Time complexity O(N * log N) where N = points.size()
    //!          Space complexity O(N)

    auto output = points;

    std::sort(output.begin(),
              output.end(),
              [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                  return (lhs[0] * lhs[0] + lhs[1] * lhs[1])
                      > (rhs[0] * rhs[0] + rhs[1] * rhs[1]);
              });
    
    output.resize(k);
    return output;
}

//! @brief Calculate squared distance of points[i] to origin
//! @param[in] points Reference to vector of points
//! @param[in] i      Index into points to get distance for
//! @return Squared Euclidean distance from origin to points[i]
static int dist(const std::vector<std::vector<int>>& points, int i)
{
    return points[i][0] * points[i][0] + points[i][1] * points[i][1];
}

static int partition(std::vector<std::vector<int>>& points, int i, int j)
{
    const int oi {i};
    const int pivot {dist(points, i)};
    ++i;

    while (true)
    {
        while (i < j && dist(points, i) < pivot)
        {
            ++i;
        }

        while (i <= j && dist(points, j) > pivot)
        {
            --j;
        }

        if (i >= j)
        {
            break;
        }

        std::swap(points[i], points[j]);
    }

    std::swap(points[oi], points[j]);

    return j;

} // static int partition( ...

//! @brief Sort points[i:j] so smallest k elements are in points[i:(i + k - 1)]
static void sort(std::vector<std::vector<int>>& points, int i, int j, int k)
{
    if (i >= j)
    {
        return;
    }
    
    //! Get random pivot element from subarray points[i:j]
    const int pivot {
        (std::mt19937() % static_cast<std::uint32_t>(j - i + 1)) + i};
    
    std::swap(points[i], points[pivot]);

    const int mid {partition(points, i, j)};
    const int leftLength {mid - i + 1};

    if (k < leftLength)
    {
        sort(points, i, mid - 1, k);
    }
    else if (k > leftLength)
    {
        sort(points, mid + 1, j, k - leftLength);
    }
}

//! @brief Discussion solution: Divide and Conquer
//! @param[in] points Reference to vector of points[i] = [x_i, y_i]
//! @param[in] k      Number of closest points to retrieve
//! @return Vector of k closest points to origin
static std::vector<std::vector<int>> kClosestDS2(
    const std::vector<std::vector<int>>& points, int k)
{
    //! @details leetcode.com/problems/k-closest-points-to-origin/editorial
    //!
    //!          Time complexity O(N) in average case and O(N^2) in worst case
    //!          where N = points.size()
    //!          Space complexity O(N)
    
    auto point_vec = points;
    sort(points, 0, static_cast<int>(points.size()) - 1, k);
    point_vec.resize(k);
    return point_vec;
}

TEST(KClosestTest, SampleTest1)
{
    const std::vector<std::vector<int>> points {{1, 3}, {-2, 2}};
    const std::vector<std::vector<int>> expected_output {{-2, 2}};

    EXPECT_EQ(expected_output, kClosestFA(points, 1));
    EXPECT_EQ(expected_output, kClosestDS1(points, 1));
    EXPECT_EQ(expected_output, kClosestDS2(points, 1));
}

TEST(KClosestTest, SampleTest2)
{
    const std::vector<std::vector<int>> points {{3, 3}, {5, -1}, {-2, 4}};
    const std::vector<std::vector<int>> expected_output {{3, 3}, {-2, 4}};

    EXPECT_EQ(expected_output, kClosestFA(points, 2));
    EXPECT_EQ(expected_output, kClosestDS1(points, 2));
    EXPECT_EQ(expected_output, kClosestDS2(points, 2));
}