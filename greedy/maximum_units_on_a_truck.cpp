#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

//! @struct Box_type
//! @brief Stores an entry at index i from boxTypes vector
struct Box_type
{
    int num_boxes {};
    int num_units {};

    //! Implicit conversion from vector to Box_type (converting constructor)
    Box_type(const std::vector<int>& box_type)
        : num_boxes {box_type[0]}
        , num_units {box_type[1]}
    {
    }

    /*
    friend operator<(const Box_type& lhs, const Box_type& rhs)
    {
        return std::tie(lhs.num_units, lhs.num_boxes)
           < std::tie(rhs.num_units, rhs.num_boxes);
    }
     */
};

//! @brief First attempt solution to get total units that can be put on truck
//! @param[in] boxTypes  Reference to vector of <num boxes, num units per box>
//! @param[in] truckSize Maximum number of boxes that can be put on truck
//! @return Maximum total number of units that can be put on the truck
static int maximumUnitsFA(
    const std::vector<std::vector<int>>& boxTypes, int truckSize)
{
    //! @details Time complexity O(N * log N) where N = boxTypes.size().
    //!          Converting from boxTypes to maxHeap costs O(N). In the worst
    //!          case, need to pop all N elements from maxHeap, where each pop
    //!          takes O(log N) for a total time complexity of O(N * log N).
    //!          Space complexity O(N) for maxHeap.

    auto lt = [](const Box_type& lhs, const Box_type& rhs)
    {
        return std::tie(lhs.num_units, lhs.num_boxes)
            < std::tie(rhs.num_units, rhs.num_boxes);
    };

    std::priority_queue<Box_type, std::vector<Box_type>, decltype(lt)> maxHeap (
        boxTypes.cbegin(), boxTypes.cend(), lt);
    
    int total_units {};

    while (truckSize > 0 && not maxHeap.empty())
    {
        const auto& max_type = maxHeap.top();

        total_units +=
            std::min(max_type.num_boxes, truckSize) * max_type.num_units;
        
        truckSize -= max_type.num_boxes;

        maxHeap.pop();
    }

    return total_units;

} // static int maximumUnitsFA( ...

//! @brief Array sort discussion solution (skip brute force solution)
//! @param[in] boxTypes  Reference to vector of <num boxes, num units per box>
//! @param[in] truckSize Maximum number of boxes that can be put on truck
//! @return Maximum total number of units that can be put on the truck
static int maximumUnitsDS1(
    const std::vector<std::vector<int>>& boxTypes, int truckSize)
{
    //! @details leetcode.com/problems/maximum-units-on-a-truck/editorial
    //!
    //!          Time complexity O(N * log N) where N = boxTypes.size(). Sorting
    //!          boxTypes takes O(N * log N).
    //!          Space complexity O(log N) for quicksort algorithm

    auto sortedBoxes = boxTypes;
    std::sort(sortedBoxes.begin(),
              sortedBoxes.end(),
              [](const std::vector<int>& lhs, const std::vector<int>& rhs) {
                  return lhs[1] > rhs[1];
              });
    
    int unitCount {};

    for (const auto& boxType : sortedBoxes)
    {
        const int boxCount = std::min(truckSize, boxType[0]);
        unitCount += boxCount * boxType[1];
        truckSize -= boxCount;

        if (truckSize == 0)
        {
            break;
        }
    }
    return unitCount;

} // static int maximumUnitsDS1( ...

struct Comparator
{
    bool operator()(const std::vector<int>& lhs, const std::vector<int>& rhs)
    {
        return lhs[1] < rhs[1];
    }
};

//! @brief Priority Queue discussion solution (skip brute force solution)
//! @param[in] boxTypes  Reference to vector of <num boxes, num units per box>
//! @param[in] truckSize Maximum number of boxes that can be put on truck
//! @return Maximum total number of units that can be put on the truck
static int maximumUnitsDS2(
    const std::vector<std::vector<int>>& boxTypes, int truckSize)
{
    //! @details leetcode.com/problems/maximum-units-on-a-truck/editorial
    //!
    //!          Time complexity O(N * log N) where N = boxTypes.size().
    //!          Discussion solution states adding all elements of boxTypes to
    //!          the priority queue takes O(N) but I believe that is the case
    //!          only when the relevant priority queue constructor is used. Each
    //!          push operation takes O(log N) so the total cost is O(N * log N)
    //!          https://stackoverflow.com/questions/44650882/
    //!          time-complexity-of-a-priority-queue-in-c
    //!          We continue iteration until the max heap is not empty or the
    //!          remaining truck size is greater than 0. In the worst case, we
    //!          may iterate N times and removing elements from the max heap
    //!          costs O(log N) for a total time complexity of O(N * log N).
    //!          Space complexity O(N) for the priority queue.

    std::priority_queue<std::vector<int>,
                        std::vector<std::vector<int>>,
                        Comparator> maxHeap {};
    
    for (const auto& boxType : boxTypes)
    {
        //! Initializes maxHeap in O(N * log N) which is slower than my solution
        maxHeap.push(boxType);
    }

    int unitCount {};
    while (not maxHeap.empty())
    {
        const auto top = maxHeap.top();
        maxHeap.pop();

        const int boxCount {std::min(truckSize, top[0])};
        unitCount += boxCount * top[1];
        truckSize -= boxCount;

        if (truckSize == 0)
        {
            break;
        }
    }

    return unitCount;

} // static int maximumUnitsDS2( ...

TEST(MaximumUnitsTest, SampleTest1)
{
    const std::vector<std::vector<int>> boxTypes {{1, 3}, {2, 2}, {3, 1}};

    EXPECT_EQ(8, maximumUnitsFA(boxTypes, 4));
    EXPECT_EQ(8, maximumUnitsDS1(boxTypes, 4));
    EXPECT_EQ(8, maximumUnitsDS2(boxTypes, 4));
}

TEST(MaximumUnitsTest, SampleTest2)
{
    const std::vector<std::vector<int>> boxTypes {
        {5, 10}, {2, 5}, {4, 7}, {3, 9}};

    EXPECT_EQ(91, maximumUnitsFA(boxTypes, 10));
    EXPECT_EQ(91, maximumUnitsDS1(boxTypes, 10));
    EXPECT_EQ(91, maximumUnitsDS2(boxTypes, 10));
}