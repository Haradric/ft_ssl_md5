
#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "libft.h"

#define error_return(str) do {error((str));return (1);} while(0)
#define error_custom_return(str,err) do {error((str),(err);return (1);} while(0)

void	error(const char *str)
{
	char *err_str;

	err_str = strerror(errno);
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	error_custom(const char *str, const char *err_str)
{
	write(STDERR_FILENO, "ft_ssl: ", 8);
	write(STDERR_FILENO, err_str, ft_strlen(err_str));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "\n", 1);
}

void	terminate(const char *str)
{
	error(str);
	exit(EXIT_FAILURE);
}

void	terminate_custom(const char *str, const char *err_str)
{
	error_custom(str, err_str);
	exit(EXIT_FAILURE);
}
