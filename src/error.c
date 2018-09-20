
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "libft.h"

#define error_return(str) do {error((str));return (1);} while(0)
#define error_custom_return(str,err) do {error((str),(err);return (1);} while(0)

void	error(const char *prefix, const char *str)
{
	char *err;

	assert(prefix);
	err = strerror(errno);
	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err, ft_strlen(err));
	if (str)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	write(STDERR_FILENO, "\n", 1);
}

void	error_custom(const char *prefix, const char *str, const char *err)
{
	assert(prefix && err);
	write(STDERR_FILENO, prefix, ft_strlen(prefix));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, err, ft_strlen(err));
	if (str)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, str, ft_strlen(str));
	}
	write(STDERR_FILENO, "\n", 1);
}

void	terminate(const char *prefix, const char *str)
{
	error(prefix, str);
	exit(EXIT_FAILURE);
}

void	terminate_custom(const char *prefix, const char *str, const char *err)
{
	error_custom(prefix, str, err);
	exit(EXIT_FAILURE);
}
