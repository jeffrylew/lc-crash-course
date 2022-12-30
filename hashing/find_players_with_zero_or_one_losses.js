/**
 * @param {number[][]} matches
 * @returns {number[][]}
 */
const findWinners = (matches) => {
    let lossesCount = new Map();
    for (const match of matches)
    {
        const winner = match[0];
        const loser  = match[1];
        lossesCount.set(winner, (lossesCount.get(winner) || 0));
        lossesCount.set(loser, (lossesCount.get(loser) || 0) + 1);
    }

    let no_losses = [];
    let one_loss  = [];
    for (const player of Array.from(lossesCount.keys()))
    {
        if (lossesCount.get(player) == 0)
        {
            no_losses.push(player);
        }
        else if (lossesCount.get(player) == 1)
        {
            one_loss.push(player);
        }
    }

    no_losses.sort((a, b) => a - b);
    one_loss.sort((a, b) => a - b);

    return [no_losses, one_loss];
}