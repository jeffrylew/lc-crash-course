#include <gtest/gtest.h>

#include <cmath>
#include <vector>

//! @brief Determine if can reach office within limit hours given speed of train
//! @param[in] speed     Speed of all trains
//! @param[in] limit     Amount of time to reach the office
//! @param[in] distances Vector of N train distances
//! @return True if can arrive at office on time if each departs at int hour
static bool check(double speed, double limit, const std::vector<int>& distances)
{
    double time {};

    for (double dist : distances)
    {
        //! Trains only depart on integer hours so round up time
        //! Rounding up simulates waiting for next train at next integer hour
        //! Don't take ceil of final time since no more trains to wait for
        time = std::ceil(time);
        time += dist / speed;
    }

    return time <= limit;
}

//! @brief Get min speed that all trains must travel at to reach office on time
//! @param[in] dist Reference to vector of N train ride distances
//! @param[in] hour Amount of time to reach the office
//! @return Min positive speed of all trains to reach office or -1 if impossible
static int minSpeedOnTime(const std::vector<int>& dist, double hour)
{
    //! @details
    //!     leetcode.com/problems/minimum-speed-to-arrive-on-time/description
    //!
    //!     Time complexity O(N) where N = dist.size() since the max possible
    //!     speed is 10^7 and the log of this is a constant. However, it would
    //!     be more appropriate to say O(N * log k), where k is the max possible
    //!     speed/answer.
    //!     Speed complexity O(1) for a few integer variables

    //! Each train departs at an integer hour. If there are more trains than
    //! hours allowed then it is impossible to reach office within hour
    if (static_cast<double>(dist.size()) > std::ceil(hour))
    {
        return -1;
    }

    //! Minimum possible speed is 1 and max is 10^7 as given in problem
    //! If the max speed isn't given, can use an arbitrarily large number for
    //! right like 10^10 - logarithms are so fast that it hardly matters.
    int left {1};
    int right {static_cast<int>(std::pow(10, 7))};

    while (left <= right)
    {
        const int mid {left + (right - left) / 2};

        if (check(mid, hour, dist))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;

} // static int minSpeedOnTime( ...

TEST(MinSpeedOnTimeTest, SampleTest)
{
    const std::vector<int> dist {1, 3, 2};

    EXPECT_EQ(1, minSpeedOnTime(dist, 6.0));

    EXPECT_EQ(3, minSpeedOnTime(dist, 2.7));

    EXPECT_EQ(-1, minSpeedOnTime(dist, 1.9));
}