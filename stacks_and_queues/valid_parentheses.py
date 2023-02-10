def isValid(s: str) -> bool:
    stack = []
    matching = {"(": ")", "[": "]", "{": "}"}

    for c in s:
        # If c is an opening bracket
        if c in matching:
            stack.append(c)
        else:
            if not stack:
                return False
            
            previous_opening = stack.pop()
            if matching[previous_opening] != c:
                return False
            
    return not stack
