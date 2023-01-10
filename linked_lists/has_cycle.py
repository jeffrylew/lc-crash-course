class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def hasCycle(head: Optional[ListNode]) -> bool:
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return True
    
    return False

def hasCycleSet(head: Optional[ListNode]) -> bool:
    seen = set()
    while head:
        if head in seen:
            return True
        
        seen.add(head)
        head = head.next
    
    return False
