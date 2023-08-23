from heapq import *
from operator import itemgetter


def maximumUnitsDS1(boxTypes: list[list[int]], truckSize: int) -> int:
    boxTypes.sort(key=itemgetter(1), reverse=True)

    unit_count = 0
    for box_type in boxTypes:
        box_count = min(truckSize, box_type[0])
        unit_count += box_count * box_type[1]
        truckSize -= box_count

        if truckSize == 0:
            break
    
    return unit_count


def maximumUnitsDS2(boxTypes: list[list[int]], truckSize: int) -> int:
    box_types = [[-box_type[1], -box_type[0]] for box_type in boxTypes]
    heapify(box_types)

    unit_count = 0
    while box_types:
        neg_top = heappop(box_types)
        box_count = min(truckSize, -neg_top[1]) # -neg_top[1] = num of boxes
        unit_count += box_count * -neg_top[0] # -neg_top[0] = units per box
        truckSize -= box_count

        if truckSize == 0:
            break
    
    return unit_count