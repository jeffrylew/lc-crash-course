#pragma once

#include <unordered_map>

template <typename T>
struct TrieNode
{
    T data {};

    std::unordered_map<char, TrieNode> children {};
};
