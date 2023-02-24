def simplifyPath(path: str) -> str:
    # Initialize a stack
    stack = []

    # Split the input string on "/" as the delimiter
    # and process each portion one by one
    for portion in path.split("/"):

        # If current component is a ".." then pop an
        # entry from stack if it's not empty
        if portion == "..":
            if stack:
                stack.pop()
        elif portion == "." or not portion:
            # A no-op for a "." or an empty string
            continue
        else:
            # Add legitimate directory name to stack
            stack.append(portion)
    
    # Stitch together directory names
    final_str = "/" + "/".join(stack)
    return final_str