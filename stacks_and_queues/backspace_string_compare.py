def backspaceCompare(s: str, t: str) -> bool:
    def build(s):
        stack = []
        for c in s:
            if c != "#":
                stack.append(c)
            elif stack:
                stack.pop()
        
        return "".join(stack)
    
    return build(s) == build(t)