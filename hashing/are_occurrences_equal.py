from collections import defaultdict

def areOccurrencesEqual(s: str) -> bool:
    counts = defaultdict(int)
    for c in s:
        counts[c] += 1
    
    frequencies = counts.values()
    return len(set(frequencies)) == 1