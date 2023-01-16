#include <gtest/gtest.h>

struct ListNode
{
    int val {};
    ListNode* next {nullptr};
    ListNode (int val) : val {val} {}
};

static ListNode* reverseList(ListNode* head)
{
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr)
    {
        //! Ensure we don't lose the next node
        auto nextNode = curr->next;

        //! Reverse direction of the pointer
        curr->next = prev;

        //! Set current node to prev for next node
        prev = curr;

        //! Move on
        curr = nextNode;
    }

    return prev;
}

TEST(ReverseListTest, SampleTest)
{
    ListNode zero {0};
    ListNode one {1};
    ListNode two {2};
    ListNode three {3};

    zero.next = &one;
    one.next  = &two;
    two.next  = &three;

    auto       head   = &zero;
    const auto result = reverseList(head);
    EXPECT_EQ(result->val, three.val);
}