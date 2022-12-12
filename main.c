#include "shell.h"

/**
* main - main
* @argc: void
* @argv: argument
* Return: Always 0
*/

int main(int argc, char **argv)
{
	char *prompt = "$ ", *token;
	char *command = NULL, *command_copy = NULL;
	size_t size = 0;
	ssize_t nchars_read;
	const char *delim = " \n";
	int num_tokens = 0, i = 0, status;
	pid_t child_pid;

	/* declaring void variables */
	(void)argc;

	/* loop for shell's prompt */
	while (1)
	{
		printf("%s", prompt);
		nchars_read = getline(&command, &size, stdin);

		/* check if getline failed/EOF/Ctrl+D */
		if (nchars_read == -1)
		{
			printf("Exiting Shell\n");
			return (-1);
		}

		/* allocate space for command_copy */
		command_copy = malloc(sizeof(char) * nchars_read);

		if (command_copy == NULL)
		{
			perror("bash: memory allocation error");
			return (-1);
		}

		/* copy command that was typed */
		strcpy(command_copy, command);

		/* split command into array of words */
		token = strtok(command, delim);

		/* calculate total number of tokens */
		while (token)
		{
			num_tokens++;
			token = strtok(NULL, delim);
		}
		num_tokens++;

		/* allocate space to hold array of strings */
		argv = malloc(sizeof(char*) * num_tokens);

		/* store each token in the argv array */
		token = strtok(command_copy, delim);

		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);

			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* execute the command */
		child_pid = fork();

		if (child_pid == 0)
		{
			command = argv[0];
			if(execve(command, argv, NULL) == -1)
				perror("Error");
		}

		if (child_pid > 0)
			wait(&status);
	}

	/* free allocated memory */
	free(command);
	free(command_copy);

	return (0);
}
