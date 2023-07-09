#include <gtest/gtest.h>

#include <queue>
#include <string>
#include <unordered_map>
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

//! @brief BFS solution to get shortest sequence len from beginWord to endWord
//! @param[in] beginWord std::string for starting word in sequence
//! @param[in] endWord   std::string for ending word in sequence
//! @param[in] wordList  Reference to vector of words in transformation sequence
//! @return Number of words in shortest transformation sequence
static int ladderLengthBFS(std::string                     beginWord,
                           std::string                     endWord,
                           const std::vector<std::string>& wordList)
{
    //! @details https://leetcode.com/problems/word-ladder/editorial/
    //!
    //!          Time complexity O(M^2 * N) where M = length of each word and
    //!          N is total number of words in word list. For each word in word
    //!          list, we iterate over its length M to find all intermediate
    //!          words corresponding to it. The total number of iterations to
    //!          create allComboMap is M * N. Forming each intermediate word
    //!          takes O(M) because of the substring operation. This leads to
    //!          a complexity of O(M^2 * N). Additionally, BFS in the worst case
    //!          might traverse all N words. For each, need to examine M
    //!          possible intermediate words/combinations. Since the substring
    //!          operation is used to find each, the M combinations take O(M^2).
    //!          Thus, the BFS time complexity is also O(M^2 * N).
    //!          Space complexity O(M^2 * N). Each word in the word list has M
    //!          intermediate combinations. To create allComboMap, we save an
    //!          intermediate word as the key and its corresponding original
    //!          words of length M as the value. So for every word we need space
    //!          O(M^2) to save all transformations corresponding to it. Thus,
    //!          allComboMap needs a total space of O(M^2 * N). The visited set
    //!          needs a space of O(M * N). Finally, the BFS queue would need
    //!          space for all O(N) words in the worst case, resulting in space
    //!          complexity O(M * N).
    //!          Optimization: Space complexity can be reduced by storing the
    //!          indices corresponding to each word instead of the word itself.

    //! All words are of same length
    const auto L = static_cast<int>(beginWord.size());

    //! Map holding combination of words that can be formed from any given word
    //! by changing one letter at a time
    std::unordered_map<std::string, std::vector<std::string>> allComboMap {};

    for (const auto& word : wordList)
    {
        for (int i = 0; i < L; ++i)
        {
            //! Key is the generic word
            //! Value is list of words that have same intermediate generic word
            const auto newWord = word.substr(0, i) + "*" + word.substr(i + 1);

            allComboMap[newWord].push_back(word);
        }
    }

    //! queue for BFS
    std::queue<std::pair<std::string, int>> queue {};
    queue.emplace(beginWord, 1);

    //! visited set to avoid processing same word
    std::unordered_set<std::string> visited({beginWord});

    while (not queue.empty())
    {
        const auto [word, level] = queue.front();
        queue.pop();

        for (int i = 0; i < L; ++i)
        {
            //! Intermediate words for current word
            const auto newWord = word.substr(0, i) + "*" + word.substr(i + 1);

            if (allComboMap.count(newWord) == 0)
            {
                continue;
            }

            //! Next states are all words that share same intermediate state
            for (const auto& adjacentWord : allComboMap[newWord])
            {
                if (adjacentWord == endWord)
                {
                    return level + 1;
                }

                if (visited.count(adjacentWord) == 0)
                {
                    visited.emplace(adjacentWord);
                    queue.emplace(adjacentWord, level + 1);
                }
            }
        }
    }

    return 0;

} // static int ladderLengthBFS( ...

TEST(LadderLengthTest, SampleTest1)
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log", "cog"};
    
    EXPECT_EQ(5, ladderLengthFA("hit", "cog", wordList));
    EXPECT_EQ(5, ladderLengthBFS("hit", "cog", wordList));
}

TEST(LadderLengthTest, SampleTest2)
{
    const std::vector<std::string> wordList {
        "hot", "dot", "dog", "lot", "log"};
    
    EXPECT_EQ(0, ladderLengthFA("hit", "cog", wordList));
    EXPECT_EQ(0, ladderLengthBFS("hit", "cog", wordList));
}