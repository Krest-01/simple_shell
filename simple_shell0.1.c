#include <stdio.h>
#include "main.h"

/**
 * main - A simple shell
 * @child_pid: stores the value return by the fork function
 * @command: stores input from stdin
 * Return: Alway return 0
 **/

int main(void)
{
	char command[100];
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("Alx_simple-shell$ ");


		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			printf("\n");
			break;
		}

		size_t len = strlen(command);

		if (len > 0 && command[len - 1] == '\n')
		{
			command[len - 1] = '\0';
		}


		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			if (execve(command, (char *const []){command, NULL}, (char *const []){NULL}))
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}



	return (0);
}
