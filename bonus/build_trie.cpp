#include "trienode.hpp"

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <vector>

//! @brief Build trie/prefix tree storing chars of a string at each node
//! @param[in] word Reference to vector of words to create trie from
//! @return Root TrieNode
static TrieNode<int> buildTrie(const std::vector<std::string>& words)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /714/bonus/4549/
    //!
    //!          Time complexity O(N * K) where N = words.size() and K = average
    //!          length of string in words.

    TrieNode<int> root {};

    for (const auto& word : words)
    {
        auto* curr = &root;
        for (const char letter : word)
        {
            auto [child_it, exists] = curr->children.try_emplace(
                letter, std::make_unique<TrieNode<int>>());

            curr = child_it->second.get();
        }

        //! At this point we have a full word at curr
        //! Can perform more logic here to give curr an attribute
    }

    return root;
}

TEST(BuildTrieTest, SampleTest1)
{
    const std::vector<std::string> words {"abcde"};

    const auto root = buildTrie(words);
    EXPECT_EQ(root.children.size(), 1U);
    EXPECT_GT(root.children.count('a'), 0U);
}
