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

//! @brief Discussion solution to get min number of mutations
//! @param[in] startGene Starting gene string, 8 chars long
//! @param[in] endGene   Ending gene string, 8 chars long
//! @param[in] bank      Reference to vector of valid gene mutations
//! @return Minimum number of mutations to mutate from startGene to endGene
static int minMutationDS(std::string                     startGene,
                         std::string                     endGene,
                         const std::vector<std::string>& bank)
{
    //! @details https://leetcode.com/problems/minimum-genetic-mutation/editorial
    //!
    //!          Time complexity O(B) where B = bank.size(). Since the problem
    //!          stated 0 <= bank.size() <= 10, conversion to an unordered_set
    //!          might be slower due to the hashing overhead. Checking if
    //!          neighbor is in the bank costs O(B). Technically this problem is
    //!          O(1) because gene strings have size 8 and there are 4 chars.
    //!          If the gene strings had length n and could have m characters
    //!          then there would be m^n possible nodes (for each of n chars
    //!          there are m options). Assuming bank is converted to a set prior
    //!          to BFS then we have O(n * B + m^n * n^2 * m). Converting bank
    //!          costs O(n * B) and there are m^n states. At each state we
    //!          perform a nested for loop that iterates n * m times and perform
    //!          string operations which cost O(n).
    //!          Space complexity O(1) since the problem limits the input. With
    //!          the same scenario as above, the space complexity is
    //!          O(n * B + m^n). Converting bank to a set creates a set taking
    //!          up O(n * B) space and the seen set could grow to m^n if all
    //!          states are visited.

    std::queue<std::string>         queue({startGene});
    std::unordered_set<std::string> seen {startGene};

    int steps {};

    while (not queue.empty())
    {
        const auto nodesInQueue = static_cast<int>(queue.size());

        for (int j = 0; j < nodesInQueue; ++j)
        {
            const auto node = queue.front();
            queue.pop();

            if (node == endGene)
            {
                return steps;
            }

            for (char c : "ACGT")
            {
                for (int i = 0; i < static_cast<int>(node.size()); ++i)
                {
                    auto neighbor = node;
                    neighbor[i]   = c;

                    if (seen.count(neighbor) == 0
                        && std::find(bank.cbegin(), bank.cend(), neighbor)
                        != bank.cend())
                    {
                        queue.push(neighbor);
                        seen.insert(neighbor);
                    }
                }
            }
        }

        ++steps;
    }

    return -1;

} // static int minMutationDS( ...

TEST(MinMutationTest, SampleTest1)
{
    const std::vector<std::string> bank {"AACCGGTA"};

    EXPECT_EQ(1, minMutationFA("AACCGGTT", "AACCGGTA", bank));
    EXPECT_EQ(1, minMutationDS("AACCGGTT", "AACCGGTA", bank));
}

TEST(MinMutationTest, SampleTest2)
{
    const std::vector<std::string> bank {"AACCGGTA", "AACCGCTA", "AAACGGTA"};

    EXPECT_EQ(2, minMutationFA("AACCGGTT", "AAACGGTA", bank));
    EXPECT_EQ(2, minMutationDS("AACCGGTT", "AAACGGTA", bank));
}

TEST(MinMutationTest, SampleTest3)
{
    const std::vector<std::string> bank {
        "AACCGATT", "AACCGATA", "AAACGATA", "AAACGGTA"};

    EXPECT_EQ(4, minMutationFA("AACCGGTT", "AAACGGTA", bank));
    EXPECT_EQ(4, minMutationDS("AACCGGTT", "AAACGGTA", bank));
}