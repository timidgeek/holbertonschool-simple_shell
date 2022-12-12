#ifndef SHELL_H
#define SHELL_H
/* --- libraries --- */
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>
#define PROMPT "$ "
#define DELIM " \n"

/* --- structures --- */

/* --- environment prototypes --- */
extern char **environ;

/* --- helpers.c --- */
char **split_string(char *str, const char *delim);
void execute(char **cmd);

/* --- built-in commands --- */
char *prompt(char *p);

#endif /* SHELL_H */
