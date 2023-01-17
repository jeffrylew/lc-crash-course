class ListNode
{
    constructor(val)
    {
        this.val = val;
        this.next = null;
    }
}

const reverseList = head => {
    let prev = null;
    let curr = head;

    while (curr)
    {
        // Ensure we don't lose the next node
        const nextNode = curr.next;

        // Reverse direction of the pointer
        curr.next = prev;

        // Set current node to prev for next node
        prev = curr;

        // Move on
        curr = nextNode;
    }

    return prev;
}