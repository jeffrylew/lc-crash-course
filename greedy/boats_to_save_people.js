/**
 * @param {number[]} people
 * @param {number} limit
 * @returns {number}
 */
var numRescueBoats = function(people, limit)
{
    let ans = 0;
    let lightest_idx = 0;
    let heaviest_idx = people.length - 1;
    people.sort((a, b) => a - b);

    while (lightest_idx <= heaviest_idx)
    {
        if (people[lightest_idx] + people[heaviest_idx] <= limit)
        {
            lightest_idx++;
        }

        heaviest_idx--;
        ans++;
    }

    return ans;
}