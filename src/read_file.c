
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
	{
		perror("ft_ssl");
		exit(EXIT_FAILURE);
	}
	ft_memset(buff, 0, BUFFSIZE);
	free(tmp);
	return (0);
}

char		*read_stdin(void)
{
	char	buff[BUFFSIZE + 1];
	char	*ret;
	size_t	i;

	if ((ret = ft_strdup("")) == NULL)
		terminate("exit");
	ft_memset(buff, 0, BUFFSIZE + 1);
	while ((i = read(STDIN_FILENO, buff, BUFFSIZE)) > 0)
	{
//		if (buff[i - 1] == '\n')
//			buff[i - 1] = 0;
		add_to_str(&ret, buff);
		ft_memset(buff, 0, BUFFSIZE);
	}
	return (ret);
}

//char		*read_file(char *path, int fd, size_t size)
//{
//	struct stat	st;
//	char		*buff;
//	size_t		i;
//
//	if (fstat(fd, &st) == -1 || \
//		(buff = mmap(NULL, st.st_size, PROT_READ, MAP_ANON, fd, 0)) == MAP_FAILED)
//	{
//		perror("ft_ssl");
//		return (NULL);
//	}
//
//
//	ft_memset(buff, 0, BUFFSIZE + 1);
//	i = 0;
//	while (read(fd, buff + i, 1) > 0)
//	{
//		if (i == BUFFSIZE - 1)
//		{
//			add_to_str(&ret, buff);
//			i = -1;
//		}
//		++i;
//	}
//	add_to_str(&ret, buff);
//	return (ret);
//}

//char		*read_file(int fd)
//{
//	char	buff[BUFFSIZE + 1];
//	char	*ret;
//	size_t	i;
//
//	ret = ft_strdup("");
//	if (ret == NULL)
//		terminate("exit");
//	ft_memset(buff, 0, BUFFSIZE + 1);
//	i = 0;
//	while (read(fd, buff + i, 1) > 0 && buff[i] != EOT)
//	{
//		if (i == BUFFSIZE - 1)
//		{
//			add_to_str(&ret, buff);
//			i = -1;
//		}
//		++i;
//	}
//	add_to_str(&ret, buff);
//	return (ret);
//}
