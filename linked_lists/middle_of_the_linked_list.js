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
const middleNode = head => {
    let slow = head;
    let fast = head;

    while (fast != null && fast.next != null)
    {
        slow = slow.next;
        fast = fast.next.next;
    }

    return slow;
}