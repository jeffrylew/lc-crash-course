class ListNode
{
    constructor(val)
    {
        this.val = val;
        this.next = null;
    }
}

const reverseBetween = (head, left, right) => {
    if (!head)
    {
        return null;
    }

    // Move two pointers until they reach the
    // proper starting point in the list
    let curr = head;
    let prev = null;
    while (left > 1)
    {
        prev = curr;
        curr = curr.next;
        left--;
        right--;
    }

    // The two pointers that will fix the final connections
    let con = prev;
    let tail = curr;

    // Iteratively reverse the nodes until right becomes 0
    let third = null;
    while (right > 0)
    {
        third = curr.next;
        curr.next = prev;
        prev = curr;
        curr = third;
        right--;
    }

    // Adjust the final connections as explained in the algorithm
    if (con)
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