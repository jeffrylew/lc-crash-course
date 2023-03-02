(function main() {
    // JavaScript doesn't have any built in efficient queue
    // We'll just have to use a normal array
    let queue = [];

    queue.push(1);
    queue.push(2);
    queue.push(3);

    while (queue.length)
    {
        console.log(queue.shift());
    }

    if (!queue.length)
    {
        console.log("Queue is empty!");
    }
}());