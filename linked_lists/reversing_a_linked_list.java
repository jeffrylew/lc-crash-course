class ListNode
{
    int val;
    ListNode next;
    ListNode (int val)
    {
        this.val = val;
    }
}

public ListNode reverseList(ListNode head)
{
    ListNode prev = null;
    ListNode curr = head;

    while (curr != null)
    {
        //! Ensure we don't lose the next node
        ListNode nextNode = curr.next;

        //! Reverse direction of pointer
        curr.next = prev;

        //! Set current node to prev for the next node
        prev = curr;

        //! Move on
        curr = nextNode;
    }

    return prev;
}