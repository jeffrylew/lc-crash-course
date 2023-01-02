from collections import defaultdict

def get_digit_sum(num: int):
    digit_sum = 0
    while num:
        digit_sum += num % 10
        num //= 10
    
    return digit_sum

def maximumSum1(nums: List[int]) -> int:
    dic = defaultdict(list)
    for num in nums:
        digit_sum = get_digit_sum(num)
        dic[digit_sum].append(num)
    
    ans = -1
    for key in dic:
        curr = dic[key]
        if len(curr) > 1:
            curr.sort(reverse=True)
            ans = max(ans, curr[0] + curr[1])
    
    return ans
