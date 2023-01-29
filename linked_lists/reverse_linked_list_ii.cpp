#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
};

//! @brief First attempt to reverse nodes of list from position left to right
//! @param[in] head  Pointer to head of singly linked list
//! @param[in] left  Index of left position to start reversing list from
//! @param[in] right Index of right position to end reversing list from
//! @return Pointer to head of reversed list
static ListNode* reverseBetweenFA(ListNode* head, int left, int right)
{
    auto ret_head = head;
    int  idx {};
    
    //! Keep track of node just before reversed portion of list
    auto before_rev = head;
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
    before_rev->next = prev;
    end_rev->next    = nextNode;

    return ret_head;

} // static ListNode* reverseBetweenFA( ...

TEST(ReverseBetweenTest, SampleTest)
{

}