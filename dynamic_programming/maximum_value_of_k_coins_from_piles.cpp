#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <vector>

static int maxValueOfCoinsDS1(const std::vector<std::vector<int>>& piles, int k)
{
    std::vector<std::vector<int>> memo(
        piles.size(), std::vector(k + 1, -1));

    std::function<int(int, int)> get_max_value =
        [&](int curr_pile, int remain_coins) -> int {
            if (curr_pile = static_cast<int>(piles.size()) || remain_coins == 0)
            {
                return 0;
            }

            if (memo[curr_pile][remain_coins] != -1)
            {
                return memo[curr_pile][remain_coins];
            }

            //! Skip this pile
            int max_value {get_max_value(curr_pile + 1, remain_coins)};

            int        curr_value {};
            const auto pile_size = static_cast<int>(piles[curr_pile].size());

            for (int coin = 0; coin < std::min(remain_coins, pile_size); ++coin)
            {
                curr_value += piles[curr_pile][coin];
                max_value =
                    std::max(max_value,
                             get_max_value(curr_pile + 1,
                                           remain_coins - coin - 1)
                             + curr_value);
            }

            return memo[curr_pile][remain_coins] = max_value;
        };

    return get_max_value(0, k);
}
