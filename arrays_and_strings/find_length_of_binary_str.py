def find_length_of_binary_str(s: str) -> int:
    left = curr = max_substr_length = 0
    for right in range(len(s)):
        if s[right] == "0":
            curr += 1
        
        while curr > 1:
            if s[left] == "0":
                curr -= 1
            left += 1
        
        max_substr_length = max(max_substr_length, right - left + 1)

    return max_substr_length
