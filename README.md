Simple Shell

A custom UNIX command-line interpreter written in C, designed to recreate core shell mechanics including command parsing, process management, and built-in execution.

Key Features
Command Parsing & Execution: Reads, parses, and executes user commands by launching child processes via system calls.

Path Resolution: Searches the system PATH environment variable to locate and execute binary programs.

Built-In Commands: Implemented native shell commands such as cd, exit, and env.

Process & Signal Handling: Manages process creation using fork and execve, while handling standard signals gracefully.

Tech Stack & Tools
Language: C

Compiler: GCC / Clang

Concepts: System Calls (fork, execve, wait, pipe), UNIX Process Management, Memory Management

Version Control: Git & GitHub

Getting Started
Prerequisites
GCC compiler or any C development toolchain

Linux/UNIX environment or WSL (Windows Subsystem for Linux)

Compilation & Setup
Clone the repository:
git clone https://github.com/Evis0/simple-shell.git
cd simple-shell

Compile the source files:
gcc -Wall -Werror -Wextra -pedantic *.c -o simple_shell

Run the shell:
./simple_shell

Built-in Commands


cd [directory]

cd: Takes you to your HOME directory.

cd -: Takes you back to the previous folder (OLDPWD).

cd <path>: Moves to a specific folder path.

exit [status]

exit: Closes the shell with status 0.

exit <status>: Closes the shell with a specific exit status code.

env: Prints all environment variables.

setenv <variable> <value>: Creates or updates an environment variable.

unsetenv <variable>: Deletes an environment variable.

Regular Commands & Programs
System Commands (ls, pwd, mkdir, grep, cat, rm):

Automatically searches your system PATH directories to find and run standard Linux commands.

Direct File Paths (/bin/ls, ./my_program):

Runs any program directly using its exact file path.

Special Characters
; (Semicolon): Run multiple commands on one line.

Example: ls; pwd; env

# (Comment): Everything after # is ignored.

Example: ls -l # list files

Ctrl+D (EOF): Exits the shell cleanly.
