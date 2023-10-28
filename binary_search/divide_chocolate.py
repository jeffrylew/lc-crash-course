def maximizeSweetness(sweetness: list[int], k: int) -> int:
    # Initialize the left and right boundaries
    # left = 1
    # right = (total sweetness) / (number of people)
    number_of_people = k + 1
    left = min(sweetness)
    right = sum(sweetness) // number_of_people

    while left < right:
        # Get middle index between left and right boundary indices
        # cur_sweetness = total sweetness for current person
        # people_with_chocolate = number of people that have a piece of
        # chocolate with sweetness greater than or equal to mid
        mid = (left + right + 1) // 2
        cur_sweetness = 0
        people_with_chocolate = 0

        # Start assigning chunks to current person
        for chunk_sweetness in sweetness:
            cur_sweetness += chunk_sweetness

            # If total sweetness is no less than mid then can break off current
            # piece and move on to assigning chunks to the next person
            if cur_sweetness >= mid:
                people_with_chocolate += 1
                cur_sweetness = 0

        if people_with_chocolate >= number_of_people:
            left = mid
        else:
            right = mid - 1

    return right


def maximizeSweetnessSA(sweetness: list[int], k: int) -> int:
    # Initialize the left and right boundaries
    # left = 1
    # right = total sweetness / number of people
    number_of_people = k + 1
    left = min(sweetness)
    right = sum(sweetness) // number_of_people

    max_min_total_sweetness = 0

    while left <= right:
        mid = (left + right) // 2
        cur_sweetness = 0
        people_with_chocolate = 0

        # Start assigning chunks to current person
        for chunk_sweetness in sweetness:
            cur_sweetness += chunk_sweetness

            # When the total sweetness is no less than mid,
            # move on to assigning chunks to the next person
            if cur_sweetness >= mid:
                people_with_chocolate += 1
                cur_sweetness = 0

        if people_with_chocolate >= number_of_people:
            max_min_total_sweetness = mid
            left = mid + 1
        else:
            right = mid - 1

    return max_min_total_sweetness
