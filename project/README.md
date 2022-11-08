# Minishell 🐚

### Video Demo : https://youtu.be/xyOBTd7IWmg

## This is a command-line program using C language with bash as reference.

# Introduction

I did this project with the help of two friends, they did the "exec" for execution and the builtins. I did the rest, meaning: the parsing (at the expection of the bin_check.c file), every function in the "libft" file (which is my own librabry regrouping some usual functions), the Makefile and the main.c file.

## What is a shell ?

Simply put, the shell is a program that takes commands from the keyboard and gives them to the operating system to perform. In the old days, it was the only user interface available on a Unix-like system such as Linux. Nowadays, we have graphical user interfaces (GUIs) in addition to command line interfaces (CLIs) such as the shell.

# Implementation

The general idea for this shell is reading a string of commands in a prompt using readline. Then parse this string in tokens which will be parsed again into usable input to be executed.

### Tokenizer

After reading from the ``stdin`` we use a function we named ``ft_strtok`` which separates the string into a list taking spaces, pipes, redirections and quotes into account. For example:

```
string: echo "hello      there" how are 'you 'doing? $USER |wc -l >outfile
output: {echo, "hello      there", how, are, 'you 'doing?, pixel, |, wc, -l, >, outfile, NULL}
```
### Parser

The parser is in charge of storing the tokenized string and save it in a useful manner for the executor to use later. Our data structure is managed as follows:

```c
typedef struct s_here
{
	char	*delimiter;
	void	*next;
}				t_here;
typedef struct s_red
{
	char	*file_name;
	int		flags;
	t_here	*doc;
}			t_red;

typedef struct s_cmd
{
	int		ac;
	char	**av;
	t_red	redir_in;
	t_red	redir_out;
}			t_cmd;

typedef struct s_mini
{
	t_cmd	*cmds;
	char	**env;
	int		nb_cmd;
}			t_mini;
```

### Executor

With all our data properly on our structs, the ``executer`` has all the necessary information to execute commands. For this part we use separate processess to execute either our builtins or other commands inside child processes and redirect ``stdin`` and ``stdout`` if needed. After all commands have started running, we retrieve the exit status of the most recently executed command.

Once all commands have finished running the allocated memory is freed and a new prompt appears to read the next command.

# Builtins

We were asked to implement some basic builtins with the help of some functions, here is a brief overview of them:

| Builtin | Description | Options | Parameters | Helpful Functions |
| :-----: | :---------: | :-----: | :--------: | :---------------: |
| ``echo`` | Prints arguments separated with a space followed by a new line | ``-n`` | :heavy_check_mark: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``cd`` | Changes current working directory, updating ``PWD`` and ``OLDPWD`` | :x: | :heavy_check_mark: | [chdir](https://man7.org/linux/man-pages/man2/chdir.2.html) |
|  ``pwd``| Prints current working directory | :x: | :x: | [getcwd](https://www.man7.org/linux/man-pages/man3/getcwd.3.html) |
| ``env`` | Prints environment | :x: | :x: | [write](https://man7.org/linux/man-pages/man2/write.2.html) |
| ``export`` | Adds/replaces variable in environment | :x: | :heavy_check_mark: | :x: |
| ``unset`` | Removes variable from environment | :x: | :heavy_check_mark: | :x: |

# Installation

* Prerequisites

Make sure you have these packages installed:

```
gcc make readline (valgrind on Linux)

Note for MacOS: to install a recent version of readline, you need to use homebrew: brew install readline
```

# Basic usage

```
make && ./minishell
```

## Tests

This command line does not nearly as much as bash but it covers the basics.

Run the following command "/bin/ls -l -a -F". ls must
be properly executed with the -l, -a, -F flags and then
give back the prompt.

Try some command using pipes and/or redirections

Every implemented builtins should works as the orignal with no flag except for "echo -n".

You can export a new variable using "export key=value" and
run "echo $key" and/or check if it as been added to the environement
using "env" and then use unset key" and check again.

Tree signals are handled: crtl-C, ctrl-\, ctrl-D.

etc.