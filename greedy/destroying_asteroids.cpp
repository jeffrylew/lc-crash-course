#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

//! @brief Determine if can destroy all asteroids (mass bigger than asteroid)
//! @param[in] mass      Mass of a planet
//! @param[in] asteroids Vector of asteroid masses
//! @return True if all asteroids can be destroyed, else false
static bool asteroidsDestroyed(int mass, std::vector<int> asteroids)
{
    //! @details https://leetcode.com/problems/destroying-asteroids/
    //!
    //!          Time complexity O(N * log N) where N = asteroids.size() due to
    //!          the sort.
    //!          Space complexity probably O(log N) since some variation of
    //!          quick sort is used. See
    //!              https://stackoverflow.com/questions/68146330/
    //!              what-is-the-space-complexity-of-stdsort-in-the-c-standard-
    //!              template-library
    
    std::sort(asteroids.begin(), asteroids.end());

    long currMass = mass;

    for (const int asteroid : asteroids)
    {
        if (asteroid > currMass)
        {
            return false;
        }

        currMass += asteroid;
    }

    return true;
}

TEST(AsteroidsDestroyedTest, SampleTest)
{
    EXPECT_TRUE(asteroidsDestroyed(10, {3, 9, 19, 5, 21}));

    EXPECT_FALSE(asteroidsDestroyed(5, {4, 9, 23, 4}));
}