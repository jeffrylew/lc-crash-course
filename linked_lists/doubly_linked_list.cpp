#include <gtest/gtest.h>

#include <vector>

struct LinkedListNode {
    int val;
    LinkedListNode* next;
    LinkedListNode* prev;
    LinkedListNode(int val) : val{val}, next{nullptr}, prev{nullptr} {}
};

//! @brief Create doubly linked list 1 <-> 2 <-> 3
static std::vector<int> doublyLinkedList()
{
    LinkedListNode one {1};
    LinkedListNode two {2};
    LinkedListNode thr {3};

    one.next = &two;
    two.next = &thr;

    two.prev = &one;
    thr.prev = &two;

    LinkedListNode*  head = &one;
    std::vector<int> output {};
    while (head != nullptr)
    {
        output.emplace_back(head->val);
        head = head->next;
    }
    
    return output;
}

TEST(DoublyLinkedListTest, SampleTest)
{
    const std::vector<int> expected_output {1, 2, 3};
    EXPECT_EQ(expected_output, doublyLinkedList());
}