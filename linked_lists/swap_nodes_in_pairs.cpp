#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
};

static ListNode* swapPairs(ListNode* head)
{
    //! Check edge case: linked list has 0 or 1 nodes, just return
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    ListNode* dummy {head->next};
    ListNode* prev {nullptr};

    while (head != nullptr && head->next != nullptr)
    {
        if (prev != nullptr)
        {
            prev->next = head->next;
        }
        prev = head;

        ListNode* nextNode = head->next->next;
        head->next->next = head;

        head->next = nextNode;
        head = nextNode;

    } // while (head != nullptr && ...

    return dummy;

} // static ListNode* swapPairs(ListNode* head)