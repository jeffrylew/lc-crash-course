let printAllNodes = root => {
    let queue = [root];
    while (queue.length)
    {
        let nodesInCurrentLevel = queue.length;
        let nextQueue = [];

        for (let i = 0; i < nodesInCurrentLevel; i++)
        {
            let node = queue[i];

            // Do some logic here on the current node
            console.log(node.val);

            // Put the next level onto the queue
            if (node.left)
            {
                nextQueue.push(node.left);
            }

            if (node.right)
            {
                nextQueue.push(node.right);
            }
        }

        queue = nextQueue;
    }
}