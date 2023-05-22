/**
 * @param {number[][]} rooms
 * @returns {boolean}
 */
var canVisitAllRooms = function(rooms) {
    const dfsRecursive = node => {
        for (const neighbor of rooms[node])
        {
            if (!seen.has(neighbor))
            {
                seen.add(neighbor);
                dfsRecursive(neighbor);
            }
        }
    }

    let seen = new Set([0]);
    dfsRecursive(0);
    return seen.size = rooms.length;
}