#include <stdio.h>
#include "main.h"

/**
 * main - A simple shell
 * @child_pid: stores the value return by the fork function
 * @command: stores input from stdin
 * Return: Alway return 0
 **/

void display_prompt()
{
	write(STDOUT_FILENO, "Alx_simple-shell$ ", 18);
}

void read_command(char *command)
{
	ssize_t read_size = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);

	if (read_size <= 0)
	{
		write(STDOUT_FILENO, "\n", 1);
		_exit(0);
	}

	command[read_size - 1] = '\0';
}

void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		char *args[] = {command, command, NULL};
		execve(args[0], args, NULL);
		perror("execve");
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
        	wait(NULL);
	}
}

int main()
{
	while (1)
	{
		display_prompt();
		char command[MAX_COMMAND_LENGTH];
		read_command(command);

		execute_command(command);
	}

	return 0;
}
