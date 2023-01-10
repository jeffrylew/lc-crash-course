#include <gtest/gtest.h>

#include <tuple>
#include <unordered_set>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val{val}, next{nullptr} {}
}

//! @brief Determine if the linked list has a cycle
//! @param[in] head Pointer to head of a linked list
//! @return True if there is some node that can be reached again, else false
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

//! @brief Determine if linked list has a cycle using hash set
//! @param[in] head Pointer to head of a linked list
//! @return True if there is some node that can be reached again, else false
static bool hasCycleSet(ListNode* head)
{
    //! @details Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(N)

    std::unordered_set<ListNode*> seen {};

    while (head != nullptr)
    {
        if (seen.find(head) != seen.end())
        {
            return true;
        }
        std::ignore = seen.insert(head);
        head = head->next;
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
    EXPECT_TRUE(hasCycleSet(head));
}