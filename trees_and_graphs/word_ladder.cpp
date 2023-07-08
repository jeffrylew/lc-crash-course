#include <gtest/gtest.h>

#include <queue>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

//! @brief First attempt to get shortest sequence len from beginWord to endWord
//! @param[in] beginWord std::string for starting word in sequence
//! @param[in] endWord   std::string for ending word in sequence
//! @param[in] wordList  Reference to vector of words in transformation sequence
//! @return Number of words in shortest transformation sequence
static int ladderLengthFA(std::string                     beginWord,
                          std::string                     endWord,
                          const std::vector<std::string>& wordList)
{
    //! Convert wordList to unordered_set and create set of visited words
    std::unordered_set<std::string> wordSet(wordList.cbegin(), wordList.cend());
    std::unordered_set<std::string> visited({beginWord});

    std::queue<std::pair<std::string, int>> queue {};
    queue.emplace(beginWord, 1);

    while (not queue.empty())
    {
        const auto [currWord, numWords] = queue.front();
        queue.pop();

        if (currWord == endWord)
        {
            return numWords;
        }

        for (int i = 0; i < static_cast<int>(currWord.size()); ++i)
        {
            auto neighbor = currWord;

            for (char c : "abcdefghijklmnopqrstuvwxyz")
            {
                neighbor[i] = c;
                
                if (wordSet.count(neighbor) > 0 && visited.count(neighbor) == 0)
                {
                    queue.emplace(neighbor, numWords + 1);
                    visited.emplace(neighbor);
                }
            }
        }
    }

    return 0;

} // static int ladderLengthFA( ...

TEST(LadderLengthTest, SampleTest1)
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};
    
    EXPECT_EQ(5, ladderLengthFA("hit", "cog", wordList));
}

TEST(LadderLengthTest, SampleTest2)
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log"};
    
    EXPECT_EQ(0, ladderLengthFA("hit", "cog", wordList));
}