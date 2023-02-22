/**
 * @param {string} path
 * @return {string}
 */
var simplifyPath = function(path) {
    let stack = [];
    const components = path.split('/');

    for (const directory of components)
    {
        if (directory == "." || directory === "")
        {
            continue;
        }
        else if (directory == "..")
        {
            if (stack.length)
            {
                stack.pop();
            }
        }
        else
        {
            stack.push(directory);
        }
    }

    const output_directory = stack.join('/');
    return "/" + output_directory;
}