#include <gtest/gtest.h>

#include <map>
#include <vector>

//! @brief Get number of pairs (R, c) where row R and col C are equal
//! @param[in] grid N by N grid of integers
//! @return Number of pairs (R, C)
static int equalPairs(std::vector<std::vector<int>> grid)
{
    //! @details Time complexity O(N^2) for N x N grid. There are N^2 elements
    //!          and each element is iterated over twice initially.
    //!          Space complexity O(N^2), if all rows and columns are unique

    //! operator== is a non-member function of std::vector
    std::map<std::vector<int>, int> row_dic {};
    for (const auto& row : grid)
    {
        ++row_dic[row];
    }

    std::map<std::vector<int>, int> col_dic {};
    for (int col = 0; col < static_cast<int>(grid[0].size()); ++col)
    {
        std::vector<int> currentCol {};
        for (int row = 0; row < static_cast<int>(grid.size()); ++row)
        {
            currentCol.push_back(grid[row][col]);
        }

        ++col_dic[currentCol];
    }

    int ans {};
    /*
    for (auto [arr, val] : row_dic)
    */
    for (const auto& kv : row_dic)
    {
        const auto& arr = kv.first;
        const auto  val = kv.second;
        ans += val * col_dic[arr];
    }

    return ans;

} // static int equalPairs( ...

TEST(EqualPairsTest, SampleTest)
{
    EXPECT_EQ(1, equalPairs({{3, 2, 1},
                             {1, 7, 6},
                             {2, 7, 7}}));
}