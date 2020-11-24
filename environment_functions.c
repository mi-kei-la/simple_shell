#include "shell.h"

/**
 * _printenv - print current environment
 *
 * Loop through the array of strings environ,
 * for each string count characters, print with write
 * and then print a new line
 */

void _printenv(void)
{
	extern char **environ;
	int i;
	size_t j;

	for (i = 0; environ[i] != 0; i++)
	{
		/* loop to count characters of each string */
		for (j = 0; environ[i][j] != 0; j++)
		{
		}
		write(1, environ[i], j);
		write(1, "\n", 1);
	}
}

/**
  * _getenv - get value of environment variable
  *
  * @name: name of environment function
  *
  * Return: string with values
  */

char *_getenv(char *name)
{
	extern char **environ;
	int i; /* i loops environ */
	unsigned int j; /* j is length of string */
	unsigned int k; /* k loops to copy */
	size_t x; /* x counts chars up to = */
	char *copy;

	for (i = 0; environ[i] != NULL; i++)
	{
		for (x = 0; environ[i][x] != '='; x++)
		{
		}

		if (_strncmp(environ[i], name, x) == 0)
		{
			j = _strlen(environ[i]);
			copy = malloc(j + 1);
			for (k = 0; (k + x) <= j; k++)
				copy[k] = environ[i][x + k];
			return (copy);
		}
	}
	return (NULL);
}

/**
  * findcom - find command in the path
  *
  * @value: value of variable PATH
  * @string: string to check
  *
  * Return: path of command, original string (first token) if not found
  */

char *findcom(char *string)
{
	char *value = NULL; /* path */
	char *thingie = "/", *stok = NULL, *ptok = NULL, *find = NULL;
	struct stat buf;
	int check;

	find = malloc(1024);
	value = _getenv("PATH");
	stok = strtok(string, " "); /* we only need 1st token */

	check = stat(stok, &buf);
	if (check == 0)
		return (stok);

	ptok = strtok(value, ":");
	while (ptok != NULL)
	{
		find = _strcpy(find, ptok);
		find = strcat(find, thingie);
		find = strcat(find, stok);
		check = stat(find, &buf);
		if (check == 0)
		{
			free(stok);
			free(value);
			return (find);
		}
		ptok = strtok(NULL, ":");
	}
	free(find);
	free(value);
	return (stok);
}
