(function main() {
    let myHashMap = new Map();

    myHashMap.set(4, 83);
    console.log(myHashMap.get(4)); // Prints 83

    console.log(myHashMap.has(4)); // Prints true
    console.log(myHashMap.has(854)); // Prints false

    myHashMap.set(8, 327);
    myHashMap.set(45, 82523);

    for (const [key, val] of myHashMap)
    {
        console.log(`${key}: ${val}`);
    }
}());