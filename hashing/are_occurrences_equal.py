from collections import defaultdict, Counter

def areOccurrencesEqual(s: str) -> bool:
    counts = defaultdict(int)
    for c in s:
        counts[c] += 1
    
    frequencies = counts.values()
    return len(set(frequencies)) == 1


def areOccurrencesEqualOneLiner(s: str) -> bool:
    return len(set(Counter(s).values())) == 1
