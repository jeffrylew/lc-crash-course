class ListNode
{
    int val;
    ListNode next;
    ListNode(int val)
    {
        this.val = val;
    }
}

public ListNode swapPairs(ListNode head)
{
    if (head == null || head.next == null)
    {
        return head;
    }

    ListNode dummy = head.next;
    ListNode prev  = null;

    while (head != null && head.next != null)
    {
        if (prev != null)
        {
            prev.next = head.next;
        }

        prev = head;

        ListNode nextNode = head.next.next;

        head.next.next = head;

        head.next = nextNode;

        head = nextNode;
    }

    return dummy;
}