def makeGood(s: str) -> str:
    # Use stack to store the visited chars
    stack = []

    # Iterate over s
    for curr_char in list(s):
        # If the current char makes a pair with the last char in the stack then
        # remove both of them. Else, add current char to stack
        if stack and abs(ord(stack[-1]) - ord(curr_char)) == 32:
            stack.pop()
        else:
            stack.append(curr_char)
    
    # Returns string concatenated by all chars left in the stack
    return "".join(stack)