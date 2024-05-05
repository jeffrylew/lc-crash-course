#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

//! @struct Trie_node_FA
//! @brief Auxiliary Trie_node struct for first attempt solution
struct Trie_node_FA
{
    std::unordered_map<char, std::unique_ptr<Trie_node_FA>> children {};

    std::unordered_set<std::string> words_at_node {};
};

//! @class TrieFA
//! @brief First attempt to implement Trie class
class TrieFA
{
    public:
        Trie() = default;

        void insert(std::string word)
        {
            auto* curr_node = &root;

            for (const char letter : word)
            {
                auto ret = curr_node->children.try_emplace(
                    letter, std::make_unique<Trie_node_FA>());

                curr_node = ret.first->second.get();

                curr_node->words_at_node.insert(word);
            }
        }

        //! @pre word is not empty
        bool search(std::string word)
        {
            auto*      curr_node = &root;
            const char first_letter {word.front()};
            if (curr_node->children.count(first_letter) == 0U)
            {
                return false;
            }

            curr_node = curr_node->children.at(first_letter).get();
            return curr_node->words_at_node.count(word) != 0U;
        }

        bool startsWith(std::string prefix)
        {
            auto* curr_node = &root;

            for (const char letter : prefix)
            {
                if (curr_node->children.count(letter) == 0U)
                {
                    return false;
                }

                curr_node = curr_node->children.at(letter).get();
            }

            return true;
        }

    private:
        Trie_node_FA root {};
};

//! @struct Trie_node_DS
//! @brief Auxiliary Trie_node struct for discussion solution
struct Trie_node_DS
{
    std::unordered_map<char, std::unique_ptr<Trie_node_DS>> children {};

    bool is_end {};
};

//! @class TrieDS
//! @brief Discussion solution for implementing Trie class
//! @details https://leetcode.com/problems/implement-trie-prefix-tree/editorial
class TrieDS
{
    public:
        TrieDS() = default;

        //! @brief Insert a word into the trie
        void insert(std::string word)
        {
            //! @details Time complexity O(M) where M = word.size(). In each
            //!          iteration of the algorithm, we examine or create a node
            //!          in the trie until the end is reached. This takes M
            //!          operations. Space complexity O(M). In the worst case,
            //!          the newly inserted word doesn't share a prefix with the
            //!          keys already inserted. Have to add M new nodes, which
            //!          takes O(M) space.

            auto* node = &root;

            for (const char curr_char : word)
            {
                auto ret = node->children.try_emplace(
                    curr_char, std::make_unique<Trie_node_DS>());

                node = ret.first->second.get();
            }

            node->is_end = true;
        }

        //! @brief Check if word is in the trie
        bool search(std::string word)
        {
            //! @details Time complexity O(M), worst case requires M operations.
            //!          Space complexity O(1)

            const auto node_ptr = search_prefix(std::move(word));
            return node_ptr != nullptr && node_ptr->is_end;
        }

        //! @brief Check if any word in the trie starts with given prefix
        //! @param[in] prefix std::string containing beginning of word to check
        bool startsWith(std::string prefix)
        {
            //! @details Time complexity O(M)
            //!          Space complexity O(1)

            return search_prefix(std::move(prefix)) != nullptr;
        }

    private:
        Trie_node_DS root {};

        //! @brief Search a prefix or whole ky in trie
        //! @return Pointer to Trie_node_DS where search ends
        Trie_node_DS* search_prefix(std::string word)
        {
            auto* node = &root;

            for (const char curr_char : word)
            {
                if (node->children.count(curr_char) == 0U)
                {
                    return nullptr;
                }

                node = node->children.at(curr_char).get();
            }

            return node;
        }
};

TEST(ImplementTrieTest, SampleTest1)
{
    TrieFA trie_FA {};
    trie_FA.insert("apple");
    EXPECT_TRUE(trie_FA.search("apple"));
    EXPECT_FALSE(trie_FA.search("app"));
    EXPECT_TRUE(trie_FA.startsWith("app"));

    trie_FA.insert("app");
    EXPECT_TRUE(trie_FA.search("app"));

    TrieDS trie_DS {};
    trie_DS.insert("apple");
    EXPECT_TRUE(trie_DS.search("apple"));
    EXPECT_FALSE(trie_DS.search("app"));
    EXPECT_TRUE(trie_DS.startsWith("app"));

    trie_DS.insert("app");
    EXPECT_TRUE(trie_DS.search("app"));
}
