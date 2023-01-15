class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def deleteDuplicates(head: Optional[ListNode]) -> Optional[ListNode]:
    current = head

    while current and current.next:
        if current.val == current.next.val:
            current.next = current.next.next
        else:
            current = current.next
    
    return head
