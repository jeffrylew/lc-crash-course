#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
};

//! @brief First attempt to reverse nodes of list from position left to right
//! @param[in] head  Pointer to head of singly linked list
//! @param[in] left  Index from 1 of left position to start reversing list from
//! @param[in] right Index from 1 of right position to end reversing list from
//! @return Pointer to head of reversed list
static ListNode* reverseBetweenFA(ListNode* head, int left, int right)
{
    auto ret_head = head;
    int  idx {1};
    
    //! Keep track of node just before reversed portion of list
    ListNode* before_rev {nullptr};
    while (idx < left && head != nullptr)
    {
        before_rev = head;
        head       = head->next;
        ++idx;
    }

    //! Keep track of original node at start of reversed portion (becomes end)
    auto end_rev = head;

    //! Auxiliary nodes to help with reversing list
    ListNode* prev = nullptr;
    auto curr      = head;

    while (idx <= right && curr != nullptr)
    {
        //! Store next node in list
        auto nextNode = curr->next;

        curr->next = prev;
        prev       = curr;
        curr       = nextNode;

        ++idx;
    }

    //! Set connections before and after reversed portion of list
    if (before_rev != nullptr)
    {
        before_rev->next = prev;
    }
    end_rev->next = curr;

    return (before_rev != nullptr) ? ret_head : prev;

} // static ListNode* reverseBetweenFA( ...

TEST(ReverseBetweenTest, SampleTest)
{
    ListNode one {1};
    ListNode two {2};
    ListNode three {3};
    ListNode four {4};
    ListNode five {5};

    one.next   = &two;
    two.next   = &three;
    three.next = &four;
    four.next  = &five;

    auto       head   = &one;
    const auto result = reverseBetweenFA(head, 2, 4);
    EXPECT_EQ(one.val, result->val);
}