def checkIfPangram1(sentence: str) -> bool:
    seen = set(sentence)

    return len(seen) == 26

def checkIfPangram2(sentence: str) -> bool:
    seen = [False] * 26

    for curr_char in sentence:
        seen[ord(curr_char) - ord('a')] = True
    
    for status in seen:
        if not status:
            return False
    
    return True

def checkIfPangram3(sentence: str) -> bool:
    seen = 0

    for curr_char in sentence:
        mapped_index = ord(curr_char) - ord('a')

        curr_bit = 1 << mapped_index

        seen |= curr_bit

    return seen == (1 << 26) - 1
