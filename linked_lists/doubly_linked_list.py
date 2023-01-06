class ListNode:
    def __init__(self, val):
        self.val = val
        self.next = None
        self.prev = None

one = ListNode(1)
two = ListNode(2)
thr = ListNode(3)

one.next = two
two.next = thr

two.prev = one
thr.prev = two

head = one
while head:
    print(head.val)
    head = head.next
