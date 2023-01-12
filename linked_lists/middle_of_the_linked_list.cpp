#include <gtest/gtest.h>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
};

//! @brief Get middle node of linked list
//! @param[in] head Pointer to head of singly linked list
//! @return Pointer to middle node
static ListNode* middleNode(ListNode* head)
{
    //! @details https://leetcode.com/problems/middle-of-the-linked-list/
    //!          solutions/154715/official-solution/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(1)

    auto slow = head;
    auto fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

TEST(MiddleNodeTest, SampleTest)
{
    ListNode one {1};
    ListNode two {2};
    ListNode three {3};
    ListNode four {4};
    ListNode five {5};

    one.next = &two;
    two.next = &three;
    three.next = &four;
    four.next = &five;

    auto       head   = &one;
    const auto result = middleNode(head);
    EXPECT_EQ(result->val, three.val);
}