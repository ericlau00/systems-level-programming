# Turtle-shell

## by Eric Lau

## Features

## Attempted

## Bugs and Notes

code exists for >< redirection but not tested

## Files and Function Headers

`execution.c`

`parse.c`

`main.c`

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
