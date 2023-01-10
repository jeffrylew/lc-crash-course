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
 * @returns {boolean}
 */
const hasCycle = head => {
    let slow = head;
    let fast = head;
    while (fast && fast.next)
    {
        slow = slow.next;
        fast = fast.next.next;
        if (slow == fast)
        {
            return true;
        }
    }

    return false;
}

/**
 * @param {ListNode} head
 * @returns {boolean}
 */
const hasCycleSet = head => {
    let seen = new Set();
    while (head)
    {
        if (seen.has(head))
        {
            return true;
        }

        seen.add(head);
        head = head.next;
    }

    return false;
}