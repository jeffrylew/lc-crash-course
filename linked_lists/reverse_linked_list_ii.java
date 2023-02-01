class ListNode
{
    int val;
    ListNode next;
    ListNode(int val)
    {
        this.val = val;
    }
}

public ListNode reverseBetween(ListNode head, int left, int right)
{
    // Empty list
    if (head == null)
    {
        return null;
    }

    // Move two pointers until they reach the
    // proper starting point in the list
    ListNode curr = head, prev = null;
    while (left > 1)
    {
        prev = curr;
        curr = curr.next;
        left--;
        right--;
    }

    // The two pointers that will fix the final connections
    ListNode con = prev, tail = curr;

    // Iteratively reverse the nodes until right becomes 0
    ListNode third = null;
    while (right > 0)
    {
        third = curr.next;
        curr.next = prev;
        prev = curr;
        curr = third;
        right--;
    }

    // Adjust the final connections as explained in the algorithm
    if (con != null)
    {
        con.next = prev;
    }
    else
    {
        head = prev;
    }

    tail.next = curr;
    return head;
}