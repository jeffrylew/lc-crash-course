/**
 * @param {number[][]} trips
 * @param {number} capacity
 * @returns {boolean}
 */
var carPooling = function(trips, capacity) {
    let farthest = 0;
    for (const trip of trips)
    {
        farthest = Math.max(farthest, trip[2]);
    }

    let change_in_passengers = new Array(farthest + 1).fill(0);
    for (const trip of trips)
    {
        const num_passengers = trip[0];
        const left = trip[1];
        const right = trip[2];

        change_in_passengers[left] += num_passengers;
        change_in_passengers[right] -= num_passengers;
    }

    let curr_passengers = 0;
    for (const passengers of change_in_passengers)
    {
        curr_passengers += passengers;
        if (curr_passengers > capacity)
        {
            return false;
        }
    }

    return true;
};
