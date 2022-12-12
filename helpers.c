#include "shell.h"

/**
* split_string - splits string by delim
* @str: input string
* @delim: delimiter
* Return: argv
*/

char **split_string(char *str, const char *delim)
{
	char *token, *command = NULL, *command_copy = NULL;
	char num_tokens = 0;
	char **argv;
	int i = 0;

	/* duplicate command that was typed */
	command_copy = strdup(str);
	command = strdup(str);

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
	argv = malloc(sizeof(char *) * num_tokens);

	/* store each token in the argv array */
	token = strtok(command_copy, delim);

	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * strlen(token));
		strcpy(argv[i], token);
		token = strtok(NULL, delim);
	}
	argv[i] = NULL;

	free(command);
	free(command_copy);
	return (argv);
}

/**
* execute - fork() and execve()
* @cmd - an array of command and its parameters
*/
void execute(char **cmd)
{
	pid_t child_pid = fork();
	int status;
	char *command;
	char **argv;

	if (child_pid == 0)
	{
		command = argv[0];
		if (execve(command, argv, NULL) == -1)
			perror("Error");
	}

	if (child_pid > 0)
		wait(&status);
}
