class ListNode
{
    int val;
    ListNode next;
    ListNode (int val)
    {
        this.val = val;
    }
}

ListNode findNode(ListNode head, int k)
{
    ListNode slow = head;
    ListNode fast = head;

    for (int i = 0; i < k; i++)
    {
        fast = fast.next; 
    }

    while (fast != null)
    {
        fast = fast.next;
        slow = slow.next;
    }

    return slow;
}