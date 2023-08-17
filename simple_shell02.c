#include <stdio.h>
#include "main.h"

/**
 * main - A simple shell that handles command line with arguments
 * @child_pid: stores the value return by the fork function
 * @command: stores input from stdin
 * Return: Alway return 0
 **/

int main(void)
{
	char command[MAX_INPUT_LENGTH];
	char *args[MAX_ARGS];
	pid_t child_pid;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "Alx_simple-shell$ ", 18);
		
		ssize_t bytes_read = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
		if (bytes_read <= 0)
		{
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		command[bytes_read - 1] = '\0';

		char *token = strtok(command, " ");
		int arg_count = 0;

		while (token != NULL && arg_count < MAX_ARGS - 1)
		{
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}
			args[arg_count] = NULL;

			child_pid = fork();
		if (child_pid == -1)
		{	perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			execve(args[0], args, NULL);
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}

	return (0);
}
