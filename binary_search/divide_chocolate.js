/**
 * @param {number[]} sweetness
 * @param {number} k
 * @returns {number}
 */
var maximizeSweetness = function(sweetness, k)
{
    // Initialize the left and right boundaries
    // left = 1
    // right = total sweetness / number of people
    const numberOfPeople = k + 1;
    let left = Math.min(...sweetness);
    let right = Math.floor(sweetness.reduce((x, y) => x + y) / numberOfPeople);

    while (left < right)
    {
        // Get middle index between left and right boundary indices
        // curSweetness        = total sweetness for current person
        // peopleWithChocolate = number of people that have a piece of chocolate
        //     with sweetness greater than or equal to mid
        const mid = Math.floor((left + right + 1) / 2);
        let curSweetness = 0;
        let peopleWithChocolate = 0;

        // Start assigning chunks to people
        for (const chunk_sweetness of sweetness)
        {
            curSweetness += chunk_sweetness;

            // If the total sweetness is no less than mid then
            // move on to assigning chunks for the next person
            if (curSweetness >= mid)
            {
                peopleWithChocolate += 1;
                curSweetness = 0;
            }
        }

        // Check if successfully gave everyone a piece of chocolate with
        // sweetness no less than mid and eliminate the search space by half
        if (peopleWithChocolate >= numberOfPeople)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    // Once the left and right boundaries coincide, we found the
    // target value which is the maximum possible sweetness
    return right;
};