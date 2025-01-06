# Definition for singly-linked list.

class ListNode:
    def __init__(self, val=0, _next=None):
        self.val = val
        self.next = _next

class Solution:
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        it = head
        result = None
        result_it = result
        while it:
            it = it.next
            num = 0
            while it and it.val != 0:
                num += it.val
                it = it.next
            if num > 0:
                if result is None:
                    result_it = ListNode(num, None)
                    result = result_it
                else:
                    result_it.next = ListNode(num, None)
                    result_it = result_it.next
        return result




