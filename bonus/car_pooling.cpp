#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Determine if possible to pick up/drop off all passengers for trips
//! @param[in] trips    Reference to vector of [numPassengers_i, from_i, to_i]
//! @param[in] capacity Number of seats in car
//! @return True if possible to pick up/drop off all passengers for all trips
static bool carPooling(const std::vector<std::vector<int>>& trips, int capacity)
{
    //! @details https://leetcode.com/problems/car-pooling/description/
    //!
    //!          Time complexity O(N + M) where N = trips.size() and M is the
    //!          farthest "to" destination in trips
    //!          Space complexity O(N + M)

    //! Get max value of "to"
    const int farthest_it {
        std::max_element(trips.begin(),
                         trips.end(),
                         [](const auto& trip_lhs, const auto& trip_rhs) {
                             return trip_lhs[2] < trip_rhs[2];
                         })};

    //! change_in_passengers indicates the change in passengers at each position
    std::vector<int> change_in_passengers(farthest_it->at(2) + 1);
    for (const auto& trip : trips)
    {
        const int num_passengers {trip[0]};
        const int left {trip[1]};
        const int right {trip[2]};

        //! num_passengers enter the car at location "left"
        change_in_passengers[left] += num_passengers;

        //! num_passengers leave the car at location "right"
        change_in_passengers[right] -= num_passengers;
    }

    //! Perform prefix sum on the road and check if number of the passengers
    //! (the prefix sum) exceeds capacity
    int curr_passengers {};
    for (const int passengers : change_in_passengers)
    {
        curr_passengers += passengers;
        if (curr_passengers > capacity)
        {
            return false;
        }
    }

    return true;

} // static bool carPooling( ...

TEST(CarPoolingTest, SampleTest1)
{
    const std::vector<std::vector<int>> trips {{2, 1, 5}, {3, 3, 7}};

    EXPECT_FALSE(carPooling(trips, 4));
}

TEST(CarPoolingTest, SampleTest2)
{
    const std::vector<std::vector<int>> trips {{2, 1, 5}, {3, 3, 7}};

    EXPECT_TRUE(carPooling(trips, 5));
}
