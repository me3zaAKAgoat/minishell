<h1 align="center"> Minishell - Crafting a Custom Shell </h1>

<div align="center">
  <img src="./readme_assets/minishell.gif" alt="minishell">
</div>

## Overview
A shell is the interface between a user and an operating system, allowing users to interact with the system via command-line inputs. Minishell is a project designed to create a basic shell, providing insights into process management and file operations. It explores core shell functionalities such as command execution, history management, and character handling.

## Understanding Shells
Shells are crucial components of Unix-like systems, offering a text-based environment for users to execute commands and automate tasks. They play a vital role in system administration, scripting, and software development.

## Key Features

- **Prompt:** Displays a prompt awaiting user commands.
- **History:** Tracks command history for easy access and repetition.
- **Command Execution:** Locates and executes commands using PATH variables or specific paths.
- **Quoting:** Handles single and double quotes to prevent misinterpretation of characters.
- **Redirections:** Manages input/output redirection and append modes.
- **Pipes:** Supports command pipelines for inter-process communication.
- **Environment Variables:** Processes variables like $PATH for dynamic command execution.
- **Built-in Commands:** Includes essential built-ins such as echo, cd, and pwd.
- **Signal Handling:** Responds to signals like ctrl-C and ctrl-D for user interaction.
- **Bash-like Behavior:** Offers behavior similar to the Bash shell for familiarity.

## References

- Unix Utilities: https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html
- Writing Your Own Shell: https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
- Signal Handling: https://faculty.cs.niu.edu/~hutchins/csci480/signals.htm
- Bash Manual: https://www.gnu.org/software/bash/manual/bash.html
- Linux Shell Development: https://www.geeksforgeeks.org/developing-linux-based-shell/
- Parsing Algorithms: https://tomassetti.me/guide-parsing-algorithms-terminology/

## Grade
<div align="center">
  <img src="./readme_assets/grade.png" alt="grade" width="150">
</div>