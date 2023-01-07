class ListNode {
    constructor(val) {
        this.val = val;
        this.next = null;
    }
}

const getMiddle = head => {
    let slow = head;
    let fast = head;

    while (fast && fast.next)
    {
        slow = slow.next;
        fast = fast.next.next;
    }

    return slow.val;
}