# OS C shell
This is a simple shell implemented by C language, as a course project of Operating System.

## To run the shell, enter the following commands:
	1. make
	2. ./terminal

MODULES:
1. shell.c: Contains main function and commands interpret function.
2. prmpt.c: Display prompt
3. input.c: Takes input from the user.
4. pwd.c: Display current directory path
5. cd.c: Change directory.
6. echo.c: Print whatever is written in front of the command.
7. ls.c: Display the contents of a directory.
8. pinfo.c: Process information of an running process.
9. jobs.c: Display bg processes with their status.
10. headers.h: Includes all the .c files and all the required modules.
11. makefile: Complile and run all .c together to make executable "terminal"
