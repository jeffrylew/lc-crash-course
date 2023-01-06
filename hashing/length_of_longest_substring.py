def lengthOfLongestSubstring(s: str) -> int:
    substr_len = left = 0

    # char_idx stores the current index of a character
    char_idx = {}

    for right in range(len(s)):
        if s[right] in char_idx:
            left = max(char_idx[s[right]], left)
        
        substr_len = max(substr_len, right - left + 1)
        char_idx[s[right]] = right + 1
    
    return substr_len
