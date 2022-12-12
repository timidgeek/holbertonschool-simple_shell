#include "shell.h"

/**
* main - main
* @argc: void
* @argv: argument
* Return: Always 0
*/

int main(int argc, char **argv)
{
	char *command = NULL, *command_copy = NULL;
	char **cmd_exec = NULL;
	ssize_t nchars_read;
	int status;
	pid_t child_pid;

	/* declaring void variables */
	(void)argc;

	/* loop for shell's prompt */
	while (1)
	{
		command = prompt(PROMPT);
		if (command == NULL)
			return (-1);

		if (command_copy == NULL)
		{
			perror("bash: memory allocation error");
			return (-1);
		}

		/* split command line and execute */
		cmd_exec = split_string(command, DELIM);
		if (cmd_exec == NULL)
		{
			free(command);
			continue;
		}

		/* execute the command */
		execute(argv);
	}

	/* free allocated memory */
	free(command);
	free(command_copy);

	return (0);
}

/**
* prompt - print the prompt for shell
* @p: the prompt
* Return: command
*/

char *prompt(char *p)
{
	size_t size = 0;
	ssize_t nchars_read;
	char *command = NULL;

	/* print prompt and read input from user */
	printf("%s", p);
	nchars_read = getline(&command, &size, stdin);

	/* check if getline failed/EOF/CTRl+D */
	if (nchars_read == -1)
	{
		printf("Exiting Shell\n");
		return (NULL);
	}

	return (command);
}
