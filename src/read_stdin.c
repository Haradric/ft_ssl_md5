
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "libft.h"
#include "ft_ssl.h"

#define BUFFSIZE 1024
#define EOT 4

static int	add_to_str(char **str, char *buff)
{
	char *tmp;

	tmp = *str;
	*str = ft_strjoin(tmp, buff);
	if (*str == NULL)
		terminate("ft_ssl", NULL);
	ft_memset(buff, 0, BUFFSIZE);
	free(tmp);
	return (0);
}

char		*read_stdin(void)
{
	char	buff[BUFFSIZE + 1];
	char	*ret;
	size_t	i;

	ret = ft_strdup("");
	if (ret == NULL)
		terminate("ft_ssl", NULL);
	ft_memset(buff, 0, BUFFSIZE + 1);
	while ((i = read(STDIN_FILENO, buff, BUFFSIZE)) > 0)
	{
		add_to_str(&ret, buff);
		ft_memset(buff, 0, BUFFSIZE);
	}
	return (ret);
}
