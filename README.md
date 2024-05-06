<h1 align=center>
 42_PIPEX 🔄
</h1>

<div align=center>
  Replicating Shell pipes in C.
</div>

# About ✍
Pipex aims to replicate the functionality of pipes found in a command-line shell. This allows different processes to communicate and exchange data with each other. In achieving this, I delved into new concepts like pipe, fork, exec, dup2, and waitpid.

# Mandatory
Pipex must replicate the behavior of piping two commands in the shell. It accepts arguments in the following format:

``
./pipex source_file command1 command2 target_file
``

This is equivalent to the shell command:

``
< source_file command1 | command2 > target_file
``

Where:

``source_file``: The path to a file containing the input data for the first command (``command1``). This file must exist.
    
``command1``: The first command. It takes the contents of ``source_file`` as input.
  
``command2``: The second command. It takes the output of ``command1`` as input.

``target_file``: The path to the file where the final output of the command-line will be written. This file may already exist, or it will be created by pipex.

In essence, pipex allows you to chain two commands together, where the output of the first becomes the input for the second. This simplifies complex tasks and streamlines data processing.

#  Walkthrough 🧩
### Parsing environment variables
I used functions from Libft to parse the environment variables. This resulted in an array of strings, each containing a possible path to the executables for the specified commands.
 ### Creating the pipe
 Pipes facilitate communication between processes. To establish a pipe, I used the `pipe()` function. This function returns an array containing two file descriptors: one for reading data from the pipe and another for writing data to the pipe.
 ### Forking the process 
 The ``fork()`` function creates a new child process that is a replica of the original process. This allows parallel execution of code within the program.
 ### Redirecting file descriptors 
 After creating a child process, ``dup2`` is used to redirect its standard input (STDIN) and standard output (STDOUT). For the child process, ``source_file`` becomes its STDIN (data source) and the pipe's write file descriptor becomes its STDOUT (output destination). On the other way, for the parent process, the pipe's read fd becomes the STDIN and the ``target_file`` becomes the parent process's STDOUT. In essence, ``dup2`` duplicates an existing fd and replaces a specified fd within the process. So the original fd (passed as the second argument) is closed to avoid leaks.
 ### Executing the processes 
 Once the file descriptors are redirected, we can execute the process. This is achieved using the ``execve`` function, that takes three arguments: a path to the executable (the path we parsed from the environment variables in the first step), the command and its arguments (an array containing the command itself and any additional arguments provided by the user) and the environment variables. If successful, ``execve`` replaces the entire process with the new program specified by the arguments. The process then starts executing the command, inheriting the redirected standard input and standard output we set up with ``dup2``. This transforms the process into the desired command, allowing it to interact with the command-line and other processes.
 ### Waiting for the child to finish
 Before the parent process can continue, it needs to ensure that all its child processes have finished execution. To achieve this, Pipex calls the ``wait`` function. This function pauses the parent process until all its child processes (in this case, one) have completed. Once this happens, the program execution concludes with the parent process finishing.

# Bonus Part

# Grade  <p><img height="30px" src="https://img.shields.io/badge/-125%20%2F%20100-success" /></p>

# Norminette 💂🏻
At 42 School, we need to follow some strict rules when writing our code. These rules are described in the Norm and checked by the formidable `norminette`. Here are some of them:
```
- No for, do...while, switch, case, goto, ternary operators and variable-length arrays are allowed
- Each function must be maximum 25 lines
- One single variable declaration per line
- You can’t declare more than 5 variables per function
- You can't write more than 5 functions per file
...
```
[Click here](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf) to review the complete Norm document.
