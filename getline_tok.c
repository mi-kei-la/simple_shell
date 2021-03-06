#include "shell.h"
/**
 * _getnewline - check new line and return exit code
 *
 * @string: received string
 * @ret: return of getline function
 * @at: return of atty
 * @she: name of the shell
 * Return: exit code
 */

int _getnewline(char *string, int ret, int at, char *she)
{
	if (ret == -1) /* if error and EOF for ctrl+d */
	{
		if (ret == EOF)
		{
			free(string);
			if (at == 1)
				write(1, "\n", 1);
			return (0); /* exit with no errors */
		}
		perror(she);
		free(string);
		return (-1); /* exit with error */
	}
	if (check(string) == 0)
	{
		free(string);
		return (3);
	}
	if (string[0] == '\n')
	{
		free(string);
		return (3); /* loop again */
	}
	if (_strncmp(string, "exit", 4) == 0)
	{
		free(string);
		return (0); /* exit with no errors */
	}
	if (_strcmp(string, "env\n") == 0)
	{
		free(string);
		_printenv();
		return (3); /* loop again */
	}
	(void)she;
	return (1); /* execute string */
}

/**
  * tokenize - load argv with string tokens
  *
  * @string: user input
  *
  * Return: double pointer (argument vector)
  */

char **tokenize(char *string)
{
	char *token = NULL; /*, *fpath = NULL;*/
	unsigned int i = 0, j = 0, toklen = 0, k = 0;
	char **toks = NULL;

	k = _strlen(string); /* assign memory to double pointer */
	toks = malloc(k * sizeof(char *));

	j = _strlen(string);
	string[j - 1] = '\0'; /* remove new line */

	token = strtok(string, " ");
	while (token != NULL)
	{
		toklen = _strlen(token);
		toks[i] = malloc(toklen + 1);
		_strcpy(toks[i], token);
		token = strtok(NULL, " "); /* go to next token */
		i++;
	}
	toks[i] = NULL; /* double pointer (vector) must end in null */
	return (toks); /* it is assigned to argv */
}

/**
  * check - check if string has readable characters
  *
  * @string: input to check
  *
  * Return: string if valid, NULL otherwise
  */

int check(char *string)
{
	int x, y = 0;

	for (x = 0; string[x] != 0; x++)
	{
		if (string[x] >= 34 && string[x] <= 125 &&
			string[x] != '.' && string[x] != '"' &&
			string[x] != '(' && string[x] != ')' &&
			string[x] != '&' && string[x] != '^' &&
			string[x] != 39 && string[x] != '>' &&
			string[x] != '<' && string[x] != '{' &&
			string[x] != '}' && string[x] != '[' &&
			string[x] != '/' && string[x] != '\\' &&
			string[x] != '|' && string[x] != '`' &&
			string[x] != ';')
			y++;
	}
	return (y);
}
