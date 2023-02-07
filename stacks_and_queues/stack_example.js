(function main() {
    let stack = [];

    stack.push(1);
    stack.push(2);
    stack.push(3);

    console.log(stack.pop());
    console.log(stack.pop());
    console.log(stack.pop());

    stack.push(5);

    if (!stack.length)
    {
        console.log("Stack is empty!");
    }
    else
    {
        console.log(`Stack is not empty, top is: ${stack[stack.length - 1]}`);
    }
}());