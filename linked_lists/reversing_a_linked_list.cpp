#include <gtest/gtest.h>

struct ListNode
{
    int val {};
    ListNode* next {nullptr};
    ListNode (int val) : val {val} {}
};

//! @brief Reverse a linked list
//! @param[in] head Pointer to head of linked list
//! @return Pointer to head of reversed linked list
static ListNode* reverseList(ListNode* head)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /704/linked-lists/4600/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(1)

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

//! @brief Reverse a linked list recursively
//! @param[in] head Pointer to head of linked list
//! @return Pointer to head of reversed linked list
static ListNode* reverseListRecursive(ListNode* head)
{
    //! @details https://leetcode.com/problems/reverse-linked-list-ii/solutions/
    //!          215957/official-solution/
    
    if (head->next == nullptr)
    {
        return head;
    }

    ListNode* last   = reverseListRecursive(head->next);
    head->next->next = head;
    head->next       = nullptr;
    return last;
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

    zero.next = &one;
    one.next  = &two;
    two.next  = &three;

    auto       headRecursive   = &zero;
    const auto resultRecursive = reverseListRecursive(headRecursive);
    EXPECT_EQ(resultRecursive->val, three.val);
}