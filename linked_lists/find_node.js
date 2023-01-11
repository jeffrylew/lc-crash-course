class ListNode
{
    constructor(val)
    {
        this.val = val;
        this.next = null;
    }
}

const findNode = (head, k) => {
    let slow = head;
    let fast = head;

    for (let i = 0; i < k; i++)
    {
        fast = fast.next;
    }

    while (fast)
    {
        fast = fast.next;
        slow = slow.next;
    }

    return slow;
}