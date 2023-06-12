#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

static std::vector<std::string> neighbors(std::string node)
{
    std::vector<std::string> ans {};

    for (int i = 0; i < 4; ++i)
    {
        const auto num = static_cast<int>(node[i]);
        for (const int change : {-1, 1})
        {
            const int x {
                (num - static_cast<int>('0') + change) % 10
                + static_cast<int>('0')};
            std::string neighbor = node;
            neighbor[i]          = x;
            ans.push_back(std::move(neighbor));
        }
    }

    return ans;
}

static int openLock(
    const std::vector<std::string>& deadends, std::string target)
{
    if (std::find(deadends.cbegin(), deadends.cend(), "0000")
        != deadends.cend())
    {
        return -1;
    }

    std::queue<std::pair<std::string, int>> queue {};
    queue.emplace("0000", 0);
    std::unordered_set<std::string> seen(deadends.begin(), deadends.end());

    while (!queue.empty())
    {
        const auto [node, steps] = queue.front();
        queue.pop();

        if (node == target)
        {
            return steps;
        }

        for (const auto& neighbor : neighbors(node))
        {
            if (seen.find(neighbor) == seen.end())
            {
                seen.insert(neighbor);
                queue.emplace(neighbor, steps + 1);
            }
        }
    }

    return -1;
}