#include <gtest/gtest.h>

struct ListNode {
    int       val;
    ListNode* next;
    ListNode(int val) : val{val}, next{nullptr} {}
};

//! @brief Return value of node in middle of linked list with odd num of nodes
//! @param[in] head Pointer to head of linked list
//! @return Value of middle node
static int getMiddle(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow->val;
}

TEST(GetMiddleTest, SampleTest)
{
    ListNode zero {0};
    ListNode one {1};
    ListNode two {2};
    ListNode three {3};
    ListNode four {4};

    zero.next  = &one;
    one.next   = &two;
    two.next   = &three;
    three.next = &four;

    EXPECT_EQ(2, getMiddle(&zero));
}