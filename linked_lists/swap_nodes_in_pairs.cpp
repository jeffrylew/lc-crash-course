#include <gtest/gtest.h>

struct ListNode
{
    int       val;
    ListNode* next;
    ListNode(int val) : val {val}, next {nullptr} {}
};

//! @brief Swap every pair of nodes in a linked list
//! @param[in] head Pointer to head of linked list
//! @return Pointer to head of swapped linked list
static ListNode* swapPairs(ListNode* head)
{
    //! @details https://leetcode.com/explore/interview/card/
    //!          leetcodes-interview-crash-course-data-structures-and-algorithms
    //!          /704/linked-lists/4600/
    //!
    //!          Time complexity O(N) where N = number of nodes in linked list
    //!          Space complexity O(1)

    //! Check edge case: linked list has 0 or 1 nodes, just return
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    //! Step 5: Save pointer to return node
    ListNode* dummy {head->next};

    //! Initialization for Step 3: Connecting swapped nodes to rest of list
    ListNode* prev {nullptr};

    while (head != nullptr && head->next != nullptr)
    {
        if (prev != nullptr)
        {
            //! Step 4: Connect swapped nodes to rest of list
            prev->next = head->next;
        }

        //! Step 3: Save pointer to first node in pair to connect to rest later
        prev = head;

        //! Step 2: Ensure can access rest of list beyond current pair
        ListNode* nextNode = head->next->next;

        //! Step 1: Perform edge swap on current pair
        head->next->next = head;

        //! Step 6: Avoid cycles for odd number of nodes
        head->next = nextNode;

        //! Move onto next pair
        head = nextNode;

    } // while (head != nullptr && ...

    return dummy;

} // static ListNode* swapPairs(ListNode* head)

TEST(SwapPairsTest, SampleTest)
{
    ListNode one {1};
    ListNode two {2};
    ListNode three {3};
    ListNode four {4};

    one.next   = &two;
    two.next   = &three;
    three.next = &four;

    auto       head   = &one;
    const auto result = swapPairs(head);
    EXPECT_EQ(result->val, two->val);
}