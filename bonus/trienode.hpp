#pragma once

#include <unordered_map>

struct TrieNode
{
    int data {};

    std::unordered_map<char, TrieNode> children {};
};
