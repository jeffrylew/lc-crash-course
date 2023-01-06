class ListNode {
    constructor(val) {
        this.val = val;
        this.next = null;
        this.prev = null;
    }
}

(function main() {
    let one = new ListNode(1);
    let two = new ListNode(2);
    let thr = new ListNode(3);

    one.next = two;
    two.next = thr;

    two.prev = one;
    thr.prev = two;

    let head = one;
    while (head)
    {
        console.log(head.val);
        head = head.next;
    }
}());