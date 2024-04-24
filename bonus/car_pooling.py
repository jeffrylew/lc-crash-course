def carPooling(trips: list[list[int]], capacity: int) -> bool:
    change_in_passengers = [0] * (max(trip[2] for trip in trips) + 1)
    for (num_passengers, left, right) in trips:
        change_in_passengers[left] += num_passengers
        change_in_passengers[right] -= num_passengers

    curr_passengers = 0
    for passengers in change_in_passengers:
        curr_passengers += passengers
        if curr_passengers > capacity:
            return False

    return True
