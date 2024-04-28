#include "trienode.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <string>
#include <vector>

//! @brief Get at most three product names after each char of searchWord
//! @param[in] products   Reference to vector of product name strings
//! @param[in] searchWord std::string to get suggested products from
//! @return Vector of suggested product vectors after each char in searchWord
static std::vector<std::vector<std::string>> suggestedProducts(
    const std::vector<std::string>& products, std::string searchWord)
{
    //! @details leetcode.com/problems/search-suggestions-system/description
    //!
    //!          Time complexity O(N * K + M) where N = products.size(),
    //!          K = average size of each product string, M = searchWord.size().
    //!          It costs O(N * K) to build a trie from products and can find
    //!          all words with matching prefixes in O(M) time.
    //!          Space complexity O(N * K), not 100% sure

    TrieNode<std::vector<std::string>> root {};

    for (const auto& product : products)
    {
        auto* node = &root;

        for (const char letter : product)
        {
            auto ret = node->children.try_emplace(
                letter, std::make_unique<TrieNode<std::vector<std::string>>>());

            node = ret.first->second.get();

            node->data.push_back(product);
            std::sort(node->data.begin(), node->data.end());
            if (node->data.size() > 3U)
            {
                node->data.pop_back();
            }
        }
    }

    std::vector<std::vector<std::string>> suggested_products {};
    auto*                                 node = &root;

    for (const char letter : searchWord)
    {
        if (node->children.count(letter) > 0U)
        {
            node = node->children[letter].get();
            suggested_products.push_back(node->data);
        }
        else
        {
            //! Deadend reached
            node->children.clear();
            suggested_products.emplace_back();
        }
    }

    return suggested_products;

} // static std::vector<std::vector<std::string>> suggestedProducts( ...

TEST(SuggestedProductsTest, SampleTest1)
{
    const std::vector<std::string> products {
        "mobile", "mouse", "moneypot", "monitor", "mousepad"};

    const std::vector<std::vector<std::string>> expected_output {
        {"mobile", "moneypot", "monitor"},
        {"mobile", "moneypot", "monitor"},
        {"mouse", "mousepad"},
        {"mouse", "mousepad"},
        {"mouse", "mousepad"}};

    EXPECT_EQ(expected_output, suggestedProducts(products, "mouse"));
}

TEST(SuggestedProductsTest, SampleTest2)
{
    const std::vector<std::string> products {"havana"};

    const std::vector<std::vector<std::string>> expected_output {
        {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}, {"havana"}};

    EXPECT_EQ(expected_output, suggestedProducts(products, "havana"));
}
