class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def find_node(head, k):
    fast = slow = head

    for _ in range(k):
        fast = fast.next
    
    while fast:
        fast = fast.next
        slow = slow.next
    
    return slow
