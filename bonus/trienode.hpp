#pragma once

#include <memory>
#include <unordered_map>

template <typename T>
struct TrieNode
{
    T data {};

    std::unordered_map<char, std::unique_ptr<TrieNode<T>>> children {};
};
