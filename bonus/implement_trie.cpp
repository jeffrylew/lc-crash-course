#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

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

TEST(ImplementTrieTest, SampleTest1)
{
    TrieFA trie_FA {};
    trie_FA.insert("apple");
    EXPECT_TRUE(trie_FA.search("apple"));
    EXPECT_FALSE(trie_FA.search("app"));
    EXPECT_TRUE(trie_FA.startsWith("app"));

    trie_FA.insert("app");
    EXPECT_TRUE(trie_FA.search("app"));
}
