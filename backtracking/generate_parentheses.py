from collections import deque


def generateParenthesisDS1(n: int) -> list[str]:
    def isValid(p_string: str) -> bool:
        left_count = 0

        for p in p_string:
            if p == '(':
                left_count += 1
            else:
                left_count -= 1

            if left_count < 0:
                return False

        return left_count == 0

    answer = []
    queue = deque([""])
    while queue:
        cur_string = queue.popleft()

        # If the length of cur_string is 2 * n,
        # add it to answer if it is valid
        if len(cur_string) == 2 * n:
            if isValid(cur_string):
                answer.append(cur_string)
            continue

        queue.append(cur_string + ")")
        queue.append(cur_string + "(")

    return answer


def generateParenthesisDS2(n: int) -> list[str]:
    answer = []

    def backtrack(cur_string: list[str], left_count: int, right_count: int):
        if len(cur_string) == 2 * n:
            answer.append("".join(cur_string))
            return

        if left_count < n:
            cur_string.append("(")
            backtrack(cur_string, left_count + 1, right_count)
            cur_string.pop()

        if right_count < left_count:
            cur_string.append(")")
            backtrack(cur_string, left_count, right_count + 1)
            cur_string.pop()

    backtrack([], 0, 0)
    return answer


def generateParenthesisDS3(n: int) -> list[str]:
    if n == 0:
        return [""]

    answer = []
    for left_count in range(n):
        for left_string in generateParenthesisDS3(left_count):
            for right_string in generateParenthesisDS3(n - 1 - left_count):
                answer.append("(" + left_string + ")" + right_string)

    return answer
