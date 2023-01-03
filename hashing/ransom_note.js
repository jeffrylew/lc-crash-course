/**
 * @param {string} ransomNote
 * @param {string} magazine
 * @returns {boolean}
 */
var canConstruct = function(ransomNote, magazine) {
    const makeCountsMap = s => {
        let counts = new Map();
        for (const c in s)
        {
            counts.set(c, (counts.get(c) || 0) + 1);
        }

        return counts;
    };

    if (ransomNote.length > magazine.length)
    {
        return false;
    }

    let magazineCounts = makeCountsMap(magazine);

    for (const c in ransomNote)
    {
        if (!magazineCounts.has(c))
        {
            return false;
        }

        const countInMagazine = magazineCounts.get(c);
        if (countInMagazine == 0)
        {
            return false;
        }

        magazineCounts.set(c, countInMagazine - 1);
    }

    return true;
}