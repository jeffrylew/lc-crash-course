def numRescueBoats(people: list[int], limit: int) -> int:
    ans = 0
    lightest_idx = 0
    heaviest_idx = len(people) - 1
    people.sort()

    while lightest_idx <= heaviest_idx:
        if people[lightest_idx] + people[heaviest_idx] <= limit:
            lightest_idx += 1
        
        heaviest_idx -= 1
        ans += 1
    
    return ans