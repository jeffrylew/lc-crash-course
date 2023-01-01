from collections import defaultdict

def minimumCardPickup1(cards: List[int]) -> int:
    dic = defaultdict(list)
    for i in range(len(cards)):
        num = cards[i]
        dic[num].append(i)
    
    ans = float("inf")
    for key in dic:
        arr = dic[key]
        for i in range(len(arr) - 1):
            ans = min(ans, arr[i + 1] - arr[i] + 1)
    
    return ans if ans < float("inf") else -1
