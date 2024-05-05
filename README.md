<h1 align=center>
 42_PIPEX 🔄
</h1>

<div align=center>
  Replicating Shell pipes in C.
</div>

# About ✍
Pipex aims to replicate the functionality of pipes found in a command-line shell. This allows different processes to communicate and exchange data with each other. In achieving this, I delved into new concepts like pipe, fork, exec, dup2, and waitpid.

# Mandatory
For the mandatory part, I needed to develop a program receiving the arguments as following:

``
 ./pipex file1 command1 command2 file2
``

It must behave exactly like the command-line :

``
 < file1 command1 | command2 > file2
``

Where:

`file1` - A file being the input to execute `command1` (must exist)

`command1` - A shell command that takes `file1` as input

`command2` - A shell command that takes as input the output of the previous process executed by `command1`

`file2` - A file being the output of the the process executed by `command2` (may exist, otherwise will be created)

# Walktrough

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
