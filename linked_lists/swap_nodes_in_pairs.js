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
const swapPairs = head => {
    if (!head || !head.next)
    {
        return head;
    }

    const ret_node = head.next;
    let   prev = null;

    while (head && head.next)
    {
        if (prev)
        {
            prev.next = head.next;
        }
        prev = head;

        const nextNode = head.next.next;
        head.next.next = head;

        head.next = nextNode;
        head = nextNode;
    }

    return ret_node;
}