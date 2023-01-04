def numJewelsInStones(jewels: str, stones: str) -> int:
    jewel_set = set(jewels)

    num_jewels = 0
    for c in stones:
        if c in jewel_set:
            num_jewels += 1
    
    return num_jewels
