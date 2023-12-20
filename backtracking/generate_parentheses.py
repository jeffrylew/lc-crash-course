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
