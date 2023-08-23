/**
 * @param {number[][]} boxTypes
 * @param {number} truckSize
 * @return {number}
 */
var maximumUnitsDS1 = function(boxTypes, truckSize)
{
    boxTypes.sort((a, b) => b[1] - a[1]);

    let unitCount = 0;

    for (const boxType of boxTypes)
    {
        const boxCount = Math.min(truckSize, boxType[0]);
        unitCount += boxCount * boxType[1];
        truckSize -= boxCount;

        if (truckSize == 0)
        {
            break;
        }
    }

    return unitCount;
};
