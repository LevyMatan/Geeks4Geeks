# pre-commit actions

If you would like to run some task before making a commit, you can easily do it using git-hooks.
I wanted to run the check-format tool before commiting to avoid many useles commits which starts with "Fix style.."

## Instructions

1. Open the terminal.

2. Navigate to the root directory of your repository.

3. Create a new file called pre-commit in the .git/hooks directory:

    ```bash
    touch .git/hooks/pre-commit
    ```

4. Make the pre-commit file executable:

    ```bash
    chmod +x .git/hooks/pre-commit
    ```

5. Open the pre-commit file in a text editor:

    ```bash
    nano .git/hooks/pre-commit
    ```

6. Add the following code to the pre-commit file:

    ```bash
    #!/bin/bash

    # Run the fix-format target
    if ! cmake --build build --target check-format; then
    echo "The check-format target failed. Aborting commit."
    echo "Running fix-format for you."
    cmake --build build --target fix-format 
    exit 1
    fi
    ```


    This code will run the first check the format, if the check fails it will run the fix-format will abort the commit.

7. Save and close the pre-commit file.

