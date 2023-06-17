/**
 * @param {character[][]} maze
 * @param {number[]} entrance
 * @return {number}
 */
var nearestExit = function(maze, entrance)
{
    const m = maze.length;
    const n = maze[0].length;
    const directions = [[-1, 0], [0, -1], [1, 0], [0, 1]];

    // Mark entrance as visited since it's not an exit
    const startRow = entrance[0];
    const startCol = entrance[1];
    maze[startRow][startCol] = '+';

    // Start BFS from the entrance and use a queue to store all cells to visit
    let queue = [[startRow, startCol, 0]];
    while (queue.length)
    {
        const currLength = queue.length;
        let nextQueue = [];

        for (let i = 0; i < currLength; i++)
        {
            const [currRow, currCol, currDistance] = queue[i];
            
            // For current cell, check its four neighbor cells
            for (const [dcol, drow] of directions)
            {
                const nextRow = currRow + drow;
                const nextCol = currCol + dcol;

                // If there exists an unvisited empty neighbor
                if (nextRow >= 0 && nextRow < m && nextCol >= 0 && nextCol < n
                    && maze[nextRow][nextCol] == '.')
                {
                    // If this empty cell is an exit, return distance + 1
                    if (nextRow == 0
                        || nextRow == m - 1
                        || nextCol == 0
                        || nextCol == n - 1)
                    {
                        return currDistance + 1;
                    }

                    // Else, add cell to queue and mark it as visited
                    maze[nextRow][nextCol] = '+';
                    nextQueue.push([nextRow, nextCol, currDistance + 1]);
                }
            }
        }

        queue = nextQueue;
    }

    // If finish iterating without finding an exit, return -1
    return -1;
};