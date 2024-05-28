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
 
# Bonus ⭐
For the bonus part, we were required to develop pipex handling multiple pipes, and also support ``<<`` and ``>>``, if ``here_doc`` is passed as the first parameter. 

So, the following command-line:

``
./pipex source_file command1 command2 command3 ... commandn target_file
``

Should behave like:

``
< source_file command1 | command2 | command3 ... | commandn > target_file
``

And also:

``
./pipex here_doc LIMITER command1 command2 target_file
``

Should behave like:

``
command1 << LIMITER | command2 >> target_file
``

Where: 

``here_doc``: Mechanism within Pipex to include multiline strings directly in the source code, becoming the STDIN of the process.

``LIMITER``: A string that defines the termination of ``here_doc``.
### Managing multiple pipes
- Looping through processes: Pipex bonus utilizes a loop to iterate through the number of commands specified, minus one, where each iteration involves forking a child process.
- Child process execution: Within the loop, the child process follows the same logic as the single-pipe scenario. It redirects its standard input (stdin) and output (stdout) using dup2 to connect with the appropriate pipe descriptors and execute the specified command.
- Parent process management: The parent process plays a crucial role in managing the pipeline. It redirects the file descriptors specifically to ensure the next child process has the correct standard input (stdin) to continue the data flow. This creates a chain where the output of one child process becomes the input for the next.
- Final process and completion: The final process in the pipeline is executed outside the loop, where it employs the ``waitpid`` function to ensure that all child processes finish execution before the program terminates. This guarantees the pipeline's sequential execution and avoids unexpected results.

### Here_doc implememtation
- Opening a new file descriptor: Using the ``open`` function, Pipex create a new fd, which will receive all the data coming from user.
- Reading user input: Through ``get_next_line`` the program captures the user's multiline input directly on the terminal.
- Writing into the file descriptor: While capturing the data, the program writes, until the string ``LIMITER`` is found, into the new fd.
- File descripton redirection: The captured input is treated as standard input for the first command in the pipeline.
- Here_doc unlinking: Before finishing the last process, Pipex deletes ``here_doc`` by calling ``unlink`` function.

  # Usage 🖥️
To install and test pipex, follow these steps:
- Clone the repository:
```bash
git clone git@github.com:marcelofassbinder/42_PIPEX.git
```
- Navigate to the project directory and run ``make`` to compile the program:
```bash
cd 42_PIPEX
make
```
- Run the program providing an existing file as input, two valid commands and a file as output. If the output file does not exist, the program will create a new one. For example:
```bash
./pipex file1 "grep a" "wc -l" file2
```
The example must result in the same output of the original shell command:
```bash
< file1 grep a | wc -l > file2
```
- For the bonus part, run:
```bash
make bonus
```
- To test a pipeline, run the program providing again, two files as input and ouput, and any commands you want, for example:
```bash
./pipex_bonus file1 "ls -l" "grep a" "wc -l" "cat"... file2 
```
- The example must result in the same output of the original shell command:
```bash
< file1 ls -l | grep a | wc -l | cat | ... > file2 
```
- To test the here_doc, run the program providing "here_doc" and a string LIMITER(delimits the end of the file) as the first and second arguments, respectively. For example:
```bash
./pipex_bonus here_doc LIMITER "ls -l" "grep a" "wc -l" "cat"... file2 
```
- The example must result in the same output of the original shell command:
```bash
ls -l << LIMITER | ls -l | grep a | wc -l | cat | ... >> file2 
```
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
