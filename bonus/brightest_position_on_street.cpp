#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <limits>
#include <utility>
#include <vector>

//! @brief First attempt solution to get smallest brightest position on street
//! @param[in] lights Reference to vector of lights[i] = [position_i, range_i]
//! @return Get brightest position (if multiple are brightest, get smallest)
static int brightestPositionFA(const std::vector<std::vector<int>>& lights)
{
    //! @details leetcode.com/problems/brightest-position-on-street/description
    //!
    //!          Time complexity O(N + M) where N = lights.size() and M is the
    //!          difference between the first and last lighted positions
    //!          Space complexity O(N + M)

    int first_lighted_pos {std::numeric_limits<int>::max()};
    int last_lighted_pos {std::numeric_limits<int>::min()};

    for (const auto& pos_range : lights)
    {
        first_lighted_pos =
            std::min(first_lighted_pos, pos_range[0] - pos_range[1]);
        last_lighted_pos =
            std::max(last_lighted_pos, pos_range[0] + pos_range[1]);
    }

    std::vector<int> brightnesses(last_lighted_pos - first_lighted_pos + 2);
    for (const auto& pos_range : lights)
    {
        const int left {(pos_range[0] - pos_range[1]) - first_lighted_pos};
        const int right {(pos_range[0] + pos_range[1]) - first_lighted_pos};

        ++brightnesses[left];
        --brightnesses[right + 1];
    }

    const auto num_positions      = static_cast<int>(brightnesses.size());
    auto       brightest_position = num_positions;
    int        curr_brightness {};
    int        max_brightness {std::numeric_limits<int>::min()};
    for (int pos = 0; pos < num_positions; ++pos)
    {
        curr_brightness += brightnesses[pos];
        if (curr_brightness > max_brightness)
        {
            brightest_position = pos;
            max_brightness     = curr_brightness;
        }
    }

    return brightest_position + first_lighted_pos;

} // static int brightestPositionFA( ...

//! @brief Discussion solution to get smallest brightest position on street
//! @param[in] lights Reference to vector of lights[i] = [position_i, range_i]
//! @return Get brightest position (if multiple are brightest, get smallest)
static int brightestPositionDS(const std::vector<std::vector<int>>& lights)
{
    //! @details leetcode.com/problems/brightest-position-on-street/description
    //!
    //!          Time complexity O(N * log N) where N = lights.size()
    //!          Space complexity O(N) for brightness_changes

    std::vector<std::pair<int, int>> brightness_changes;
    for (const auto& pos_range : lights)
    {
        const int position {pos_range[0]};
        const int radius {pos_range[1]};

        //! When enter a light's coverage, brightness increases by 1
        brightness_changes.emplace_back(position - radius, 1);

        //! When exit a light's coverage, brightness decreases by 1
        brightness_changes.emplace_back(position + radius + 1, -1);
    }

    std::sort(brightness_changes.begin(), brightness_changes.end());

    int brightest_pos {};
    int curr_brightness {};
    int max_brightness {};

    for (const auto& [position, brightness] : brightness_changes)
    {
        curr_brightness += brightness;
        if (curr_brightness > max_brightness)
        {
            max_brightness = curr_brightness;
            brightest_pos  = position;
        }
    }

    return brightest_pos;

} // static int brightestPositionDS( ...

TEST(BrightestPositionTest, SampleTest1)
{
    const std::vector<std::vector<int>> lights {{-3, 2}, {1, 2}, {3, 3}};

    EXPECT_EQ(-1, brightestPositionFA(lights));
    EXPECT_EQ(-1, brightestPositionDS(lights));
}

TEST(BrightestPositionTest, SampleTest2)
{
    const std::vector<std::vector<int>> lights {{1, 0}, {0, 1}};

    EXPECT_EQ(1, brightestPositionFA(lights));
    EXPECT_EQ(1, brightestPositionDS(lights));
}

TEST(BrightestPositionTest, SampleTest3)
{
    const std::vector<std::vector<int>> lights {{1, 2}};

    EXPECT_EQ(-1, brightestPositionFA(lights));
    EXPECT_EQ(-1, brightestPositionDS(lights));
}

TEST(BrightestPositionTest, MemoryLimitExceededTest)
{
    const std::vector<std::vector<int>> lights {
        {100000000, 100000000}, {-100000000, 100000000}};

    // EXPECT_EQ(?, brightestPositionFA(lights));
}
