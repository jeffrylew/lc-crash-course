#include <gtest/gtest.h>

#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

//! @brief First attempt solution to get min number of mutations
//! @param[in] startGene Starting gene string, 8 chars long
//! @param[in] endGene   Ending gene string, 8 chars long
//! @param[in] bank      Reference to vector of valid gene mutations
//! @return Minimum number of mutations to mutate from startGene to endGene
static int minMutationFA(std::string                     startGene,
                         std::string                     endGene,
                         const std::vector<std::string>& bank)
{
    if (startGene == endGene)
    {
        return 0;
    }

    std::unordered_set<std::string>         seen {startGene};
    std::unordered_set<std::string>         bank_set(bank.begin(), bank.end());
    std::queue<std::pair<std::string, int>> queue({{startGene, 0}});
    static const std::vector<char>          choices {'A', 'C', 'G', 'T'};

    while (not queue.empty())
    {
        const auto [gene, mutations] = queue.front();
        queue.pop();

        if (gene == endGene)
        {
            return mutations;
        }

        for (int i = 0; i < static_cast<int>(gene.size()); ++i)
        {
            for (const char c : choices)
            {
                const std::string neighbor {
                    gene.substr(0, i) + c + gene.substr(i + 1)};
            
                if (seen.count(neighbor) == 0 && bank_set.count(neighbor) == 1)
                {
                    seen.insert(neighbor);
                    queue.emplace(neighbor, mutations + 1);
                }
            }
        }
    }

    return -1;

} // static int minMutationFA( ...

TEST(MinMutationTest, SampleTest1)
{
    const std::vector<std::string> bank {"AACCGGTA"};

    EXPECT_EQ(1, minMutationFA("AACCGGTT", "AACCGGTA", bank));
}

TEST(MinMutationTest, SampleTest2)
{
    const std::vector<std::string> bank {"AACCGGTA", "AACCGCTA", "AAACGGTA"};

    EXPECT_EQ(2, minMutationFA("AACCGGTT", "AAACGGTA", bank));
}

TEST(MinMutationTest, SampleTest3)
{
    const std::vector<std::string> bank {
        "AACCGATT", "AACCGATA", "AAACGATA", "AAACGGTA"};

    EXPECT_EQ(4, minMutationFA("AACCGGTT", "AAACGGTA", bank));
}