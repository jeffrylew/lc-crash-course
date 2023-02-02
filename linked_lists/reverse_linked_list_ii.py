class ListNode:
    def __init__(self, val: int):
        self.val = val
        self.next = None

def reverseBetween(head: ListNode, left: int, right: int) -> ListNode:
    # Empty list
    if not head:
        return None
    
    # Move the two pointers until they reach the
    # proper starting point in the list
    curr, prev = head, None
    while left > 1:
        prev = curr
        curr = curr.next
        left, right = left - 1, right - 1

    # The two pointers that will fix the final connections
    tail, con = curr, prev

    # Iteratively reverse the nodes until right becomes 0
    while right:
        third = curr.next
        curr.next = prev
        prev = curr
        curr = third
        right -= 1
    
    # Adjust the final connections as explained in the algorithm
    if con:
        con.next = prev
    else:
        head = prev
    
    tail.next = curr
    return head
