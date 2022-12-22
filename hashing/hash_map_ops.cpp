#include <gtest/gtest.h>

#include <unordered_map>

TEST(HashMapOps, SampleTest)
{
    std::unordered_map<int, int> myHashMap;

    myHashMap[4] = 83;

    EXPECT_NE(myHashMap.find(4), myHashMap.end());
    EXPECT_EQ(myHashMap.find(854), myHashMap.end());

    myHashMap[8] = 327;
    myHashMap[45] = 82523;

    /*
    for (auto [key, val] : myHashMap)
    {
        std::cout << key << ": " << val << std::endl;
    }
    */
}