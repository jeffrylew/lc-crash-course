class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def get_middle(head):
    slow = fast = head

    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    
    return slow.val
