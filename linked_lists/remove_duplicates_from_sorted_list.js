class ListNode
{
    constructor(val)
    {
        this.val = val;
        this.next = null;
    }
}

/**
 * @param {ListNode} head
 * @returns {ListNode}
 */
const deleteDuplicates = head => {
    let current = head;
    while (current && current.next)
    {
        if (current.val == current.next.val)
        {
            current.next = current.next.next;
        }
        else
        {
            current = current.next;
        }
    }

    return head;
}