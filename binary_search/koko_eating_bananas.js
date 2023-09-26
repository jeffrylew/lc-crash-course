/**
 * @param {number[]} piles
 * @param {number} h
 * @return {number}
 */
var minEatingSpeed = function(piles, h)
{
    const check = k => {
        let hours = 0;

        for (const bananas of piles)
        {
            hours += Math.ceil(bananas / k);
        }

        return hours <= h;
    }

    let left = 1;
    let right = Math.max(...piles);

    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);

        if (check(mid))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
};