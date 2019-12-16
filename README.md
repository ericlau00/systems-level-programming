# Turtle-shell 

## by Eric Lau

## Features

- execute a single command on one line
- execute multiple commands on one line 
- change directories
- simple redirection with `<` and `>`
- multi redirection (e.g. `command 1 < command 2 > command3`)
- simple piping (e.g. `command 1 | command 2`)
- allows for multiple spaces between arguments and symbols (`|, <, >, ;`)

## Attempted

- when there is no argument for `cd`, change directory to home directory
- allow user to run a command like `git commit -m "a message"`
  - not splitting on quotes and making sure there are two quotes 
- display username, hostname, and current working directory at beginning of each line
  - does not display nicely when executing `./program < TEST_COMMANDS`
  
## Bugs and Notes

- code for multi-redirection in the following manner is implemented but not tested: `command 1 > command 2 < command 3`
- piping is not heavily tested

## Files and Function Headers

`execution.c` handles execution of commands 

```c
int exec_line(char *line);
/**
   Inputs: char * line 
   
   Returns: 0
   
*/


int exec_command(char * command);
/**
   Inputs: char * command
   
   Returns: 0
   
*/


int exec_redir(char * command, char std, int multi);
/**
   Inputs: char * command 
           char std
           int multi
   
   Returns: 0 
   
*/


int exec_fork(char * command, char ** args);
/**
   Inputs: char * command 
           char ** args
   
   Returns: 0
   
*/


int exec_pipe(char * command);
/**
   Inputs: char * command
   
   Returns: 0
   
*/
```

`parse.c` handles getting information on inputs and parsing commands 

```c
int stripper(char * line, char strip);
/**
   Inputs: char * line 
           char strip
   
   Returns: 0
*/


int shift(char * line, char strip);
/**
   Inputs: char * line 
           char strip
   
   Returns: 0 
   
*/


char ** parser(char * line, char delim);
/**
   Inputs: char * line 
           char delim
   
   Returns: an array of strings separated by delim 
   
   Does not add empty arguments to array
   Mallocs size of array depending on number of delimiters present 
   Adds null to end of list 
*/


int count(char * line, char delim);
/**
   Inputs: char * line 
           char delim 
   
   Returns: 1 + the number of appearances of delim in line 
*/


int get_fd(char * file, char std);
/**
   Inputs: char * file
           char std
   
   Returns: the file descriptor of the file described by char * file
   
   Considers whether the the file has already been created 
   Will create a new file if not
   Depending on what direction is being directed, will change permissions of file accordingly 
*/


int is_before(char * line, char f, char s);
/**
   Inputs: char * line 
           char f 
           char s 
   
   Returns: an integer representing whether the f character is indexed before the s character 
   
   Considers whether the char pointer of the first character is less than that of the second 
*/
```

`main.c` handles running the shell

```c
int main();
/**
   Inputs: 
   
   Returns: 0
   
   Loops as long as the user has not executed exit.
   Retrieves input, parses, and executes.
   Recurrently displays username, host, and current working directory.
*/
```

## Project 01: Shell[ing] out commands

You (and a partner if desired - highly suggested) are to write a shell. The shell should implement as many of these features as possible. The first being the most basic up to the last which is the most complex.

1. Read a line at a time, parse the line to separate the command from its arguments. It should then fork and exec the command. The parent process should wait until the exec'd program exits and then it should read the next command.
   - Note: exit and cd cannot be run through a forked child process, you will have to implement these commands on your own.
     - check out the `chdir()` function
2. Read and separate multiple commands on one line with ;. That is, the line `ls -l ; echo hello` should first run the command `ls -l` and then `echo hello`.
3. Implement simple redirection using > (redirecting stdout) and < (redirecting stdin). - **This will be explained in class**.
4. Implement simple pipes, that is: ls | wc would run ls and use the output from ls as the input for wc. - **This will be explained in class.**
   - Check out `popen()` for this.

All of these commands work in bash, so use it to check out the functionality of each feature if you are unclear about anything.

Specific requirements

1. Every function you write must have a function header describing the arguments, return value and what the function does.
   - Use modular design liberally. This is a large program.
2. You should have a readme file with the following:
   1. A description of what features your shell implements
   2. A description of what features you attempted to implement but were unsuccessful
   3. Any bugs or things you want me to know about your program
      1. I am much more forgiving of reported bugs than bugs I discover while testing
   4. A copy of every function header
   5. An example of the readme file can be found in the github repository for this assignment
3. This project should use separate C files as necessary.
4. The project should be built using make and a makefile, I will only compile by using make.

Try starting with these restrictions on input:

1. To make your life easier, you could require that all items on the command line are to be separated by a single space.
2. When parsing the line, it might help to count the number of tokens (individual pieces), before parsing.
3. You can restrict the locations and ordering of > and <.
4. You can limit piping (|) to a single pipe.
If you would like to implement other features after getting these ones down, please do. Look at what bash does and see what else you can do!

Github links (one directory per group)

<https://github.com/mks65/shell.git>
