def maxNumberOfApplesDS1(weight: list[int]) -> int:
    weight.sort()
    apples = units = 0

    for ele in weight:
        units += ele

        if units > 5000:
            break

        apples += 1
    
    return apples