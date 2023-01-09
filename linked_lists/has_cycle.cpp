#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val{val}, next{nullptr} {}
}

static bool hasCycle(ListNode* head)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /704/linked-lists/4507/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(1)

    ListNode* slow = head;
    ListNode* fast = head;

    while (fast != nullptr && fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
        {
            return true;
        }
    }

    return false;
}

TEST(HasCycleTest, SampleTest)
{
    ListNode one {1};
    ListNode two {2};
    ListNode thr {3};

    one.next = &two;
    two.next = &thr;
    thr.next = &one;

    auto head = &one;
    EXPECT_TRUE(hasCycle(head));
}