def reverseStringShort(s: List[str]) -> None:
    s.reverse()


def reverseStringRecursive(s: List[str]) -> None:
    def helper(left: int, right: int) -> None:
        if left < right:
            s[left], s[right] = s[right], s[left]
            helper(left + 1, right - 1)

    helper(0, len(s) - 1)


def reverseStringTwoPointers(s: List[str]) -> None:
    left, right = 0, len(s) - 1
    while left < right:
        s[left], s[right] = s[right], s[left]
        left, right = left + 1, right - 1

