public class Example {
    public static class ListNode {
        int val;
        ListNode next;
        ListNode prev;
        ListNode (int val) {
            this.val = val;
        }
    }

    public static void main(String[] args) {
        ListNode one = new ListNode(1);
        ListNode two = new ListNode(2);
        ListNode thr = new ListNode(3);

        one.next = two;
        two.next = thr;

        two.prev = one;
        thr.prev = two;

        ListNode head = one;
        while (head != null)
        {
            System.out.println(head.val);
            head = head.next;
        }
    }
}