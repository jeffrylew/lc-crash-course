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

TEST(MaximumUnitsTest, SampleTest1)
{
    const std::vector<std::vector<int>> boxTypes {{1, 3}, {2, 2}, {3, 1}};

    EXPECT_EQ(8, maximumUnitsFA(boxTypes, 4));
    EXPECT_EQ(8, maximumUnitsDS1(boxTypes, 4));
}

TEST(MaximumUnitsTest, SampleTest2)
{
    const std::vector<std::vector<int>> boxTypes {
        {5, 10}, {2, 5}, {4, 7}, {3, 9}};

    EXPECT_EQ(91, maximumUnitsFA(boxTypes, 10));
    EXPECT_EQ(91, maximumUnitsDS1(boxTypes, 10));
}