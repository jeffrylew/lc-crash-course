from collections import Counter

def findLeastNumOfUniqueInts(arr: list[int], k: int) -> int:
    counts = Counter(arr)
    ordered = sorted(counts.values(), reverse=True)

    while k:
        val = ordered[-1]
        if val <= k:
            k -= val
            ordered.pop()
        else:
            break
    
    return len(ordered)