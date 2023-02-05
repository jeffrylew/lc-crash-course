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

//! @brief Iterative discussion solution to reverse nodes of list
//! @param[in] head  Pointer to head of singly linked list
//! @param[in] left  Index from 1 of left position to start reversing list from
//! @param[in] right Index from 1 of right position to end reversing list from
//! @return Pointer to head of reversed list
static ListNode* reverseBetweenDS1(ListNode* head, int left, int right)
{
    //! @details https://leetcode.com/problems/reverse-linked-list-ii/solutions/
    //!          215957/official-solution/
    //!
    //!          Time complexity O(N) where N = Number of nodes in list
    //!          Space complexity O(1)

    //! Empty list
    if (head == nullptr)
    {
        return nullptr;
    }

    //! Move two pointers until they reach the
    //! proper starting point in the list
    auto      curr = head;
    ListNode* prev {nullptr};
    while (left > 1)
    {
        prev = curr;
        curr = curr->next;
        --left;
        --right;
    }

    //! Two pointers that will fix the final connections
    auto con  = prev;
    auto tail = curr;

    //! Iteratively reverse the nodes until right becomes 0
    ListNode* third {nullptr};
    while (right > 0)
    {
        third      = curr->next;
        curr->next = prev;
        prev       = curr;
        curr       = third;
        --right;
    }

    //! Adjust final connections
    if (con != nullptr)
    {
        con->next = prev;
    }
    else
    {
        head = prev;
    }

    tail->next = curr;
    return head;

} // static ListNode* reverseBetweenDS1( ...

//! @brief Recursive discussion solution to reverse nodes of list
//! @param[in] head  Pointer to head of singly linked list
//! @param[in] m     Index from 1 of left position to start reversing list from
//! @param[in] n     Index from 1 of right position to end reversing list from
//! @return Pointer to head of reversed list
static ListNode* reverseBetweenDS2(ListNode* head, int m, int n)
{
    //! @details https://leetcode.com/problems/reverse-linked-list-ii/solutions/
    //!          215957/official-solution/
    //!
    //!          Time complexity O(N) where N = Number of nodes in list.
    //!          Worst case is reversing all nodes in list (perform N/2 swaps).
    //!          Space complexity O(N). In worst case, will have N/2 recursive
    //!          calls on stack for each swap.

    ListNode* left = head;
    bool      stop {};

    recurseAndReverse(head, left, m, n, stop);
    return head;

} // static ListNode* reverseBetweenDS2( ...

static void recurseAndReverse(ListNode* right,
                              ListNode* left,
                              int       m,
                              int       n,
                              bool&     stop)
{
    //! Base case, don't proceed any further
    if (n == 1)
    {
        return;
    }

    //! Keep moving the right pointer one step forward until (n == 1)
    right = right->next;

    //! Keep moving left pointer to the right until we reach
    //! the proper node from where the reversal is to start
    if (m > 1)
    {
        left = left->next;
    }

    //! Recursve with m and n reduced
    recurseAndReverse(right, left, m - 1, n - 1, stop);

    //! In case both the pointers cross each other or become equal, we stop
    //! i.e. don't swap data any further. Done reversing at this point.
    if (left == right || right->next == left)
    {
        stop = true;
    }

    //! Until boolean stop is false, swap data between two pointers
    if (not stop)
    {
        const int init_left_val = left->val;
        left->val               = right->val;
        right->val              = init_left_val;

        //! Move left one step to the right
        //! Right pointer moves ones step back via backtracking
        left = left->next;
    }

} // static void recurseAndReverse( ...

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
    const auto resultFA = reverseBetweenFA(head, 2, 4);
    EXPECT_EQ(one.val, resultFA->val);

    one.next   = &two;
    two.next   = &three;
    three.next = &four;
    four.next  = &five;
    head       = &one;

    const auto resultDS1 = reverseBetweenDS1(head, 2, 4);
    EXPECT_EQ(one.val, resultDS1->val);

    one.next   = &two;
    two.next   = &three;
    three.next = &four;
    four.next  = &five;
    head       = &one;

    const auto resultDS2 = reverseBetweenDS2(head, 2, 4);
    EXPECT_EQ(one.val, resultDS2->val);
}