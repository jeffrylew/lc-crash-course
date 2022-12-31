const maxNumberOfBalloons = (text) => {
    let bCount = 0, aCount = 0, lCount = 0, oCount = 0, nCount = 0;
    for (const c of text)
    {
        if (c == "b")
        {
            bCount++;
        }
        else if (c == "a")
        {
            aCount++;
        }
        else if (c == "l")
        {
            lCount++;
        }
        else if (c == "o")
        {
            oCount++;
        }
        else if (c == "n")
        {
            nCount++;
        }
    }

    lCount = lCount / 2;
    oCount = oCount / 2;

    return Math.min(bCount,
                    Math.min(aCount,
                             Math.min(lCount,
                                      Math.min(oCount, nCount))));
}