class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def reverse_list(head: Optional[ListNode]) -> Optional[ListNode]:
    prev = None
    curr = head

    while head:
        # Ensure we don't lose the next node
        next_node = curr.next

        # Reverse direction of the pointer
        curr.next = prev

        # Set current node to prev for next node
        prev = curr

        # Move on
        curr = next_node
    
    return prev
