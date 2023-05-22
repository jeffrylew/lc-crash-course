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

    const dfsIterative = start => {
        let stack = [start];

        while (stack.length)
        {
            const node = stack.pop();
            for (const neighbor of rooms[node])
            {
                if (!seen.has(neighbor))
                {
                    seen.add(neighbor);
                    stack.push(neighbor);
                }
            }
        }
    }

    let seen = new Set([0]);
    dfsRecursive(0);
    // dfsIterative(0);
    return seen.size = rooms.length;
}