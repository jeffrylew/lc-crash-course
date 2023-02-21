public String simplifyPath(String path)
{
    // Initialize a stack
    Stack<String> stack = new Stack<String>();
    String[] components = path.split("/");

    // Split the input string on "/" as the delimiter
    // and process each portion one by one
    for (String directory : components)
    {
        // A no-op for a "." or an empty string
        if (directory.equals(".") || directory.isEmpty())
        {
            continue;
        }
        else if (directory.equals(".."))
        {
            // If the current component is a ".." then we pop
            // an entry from the stack if it is non-empty
            if (!stack.isEmpty())
            {
                stack.pop();
            }
        }
        else
        {
            // Add legitimate directory name to stack
            stack.add(directory);
        }
    }

    // Stitch together all the directory names together
    StringBuilder result = new StringBuilder();
    for (String dir : stack)
    {
        result.append("/");
        result.append(dir);
    }

    return result.length() > 0 ? result.toString() : "/";
}