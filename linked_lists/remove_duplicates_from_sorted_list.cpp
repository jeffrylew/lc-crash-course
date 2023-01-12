#include <gtest/gtest.h>

class ListNode
{
    int val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
}

//! @brief Delete all duplicates in sorted linked list
//! @param[in] head Pointer to head of sorted linked list
//! @return Pointer to head of sorted linked list without duplicates
static ListNode* deleteDuplicates(ListNode* head)
{
    const auto new_head = head;
    auto       slow     = head;
    auto       fast     = head;

    while (fast != nullptr)
    {
        while (slow->val == fast->val)
        {
            fast = fast->next;
            if (fast == nullptr)
            {
                break;
            }
        }
        slow->next = fast;
        slow = slow->next;
    }

    return new_head;

} // static ListNode* deleteDuplicates( ...

TEST(DeleteDuplicatesTest, SampleTest)
{
    ListNode one {1};
    ListNode one_duplicated {1};
    ListNode two {2};

    one.next            = &one_duplicated;
    one_duplicated.next = &two;

    auto head     = &one;
    auto new_head = deleteDuplicates(head);
    EXPECT_EQ(one.val, new_head->val);
    new_head = new_head->next;
    EXPECT_EQ(two.val, new_head->val);
}