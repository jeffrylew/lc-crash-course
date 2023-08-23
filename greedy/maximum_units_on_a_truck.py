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
