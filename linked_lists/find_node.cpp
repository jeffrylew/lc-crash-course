#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val{val}, next{nullptr} {}
}

//! @brief Return kth node from end of linked list
//! @param[in] head Pointer to head of linked list
//! @param[in] k    Number of nodes from end to retrieve
//! @return kth node from end
static ListNode* findNode(ListNode* head, int k)
{
    //! @details Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(1)

    ListNode* slow = head;
    ListNode* fast = head;

    for (int i = 0; i < k; ++i)
    {
        fast = fast->next;
    }

    while (fast != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }

    return slow;
}

TEST(FindNodeTest, SampleTest)
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
    const auto result = findNode(head, 2);
    EXPECT_EQ(four.val, result->val);
}