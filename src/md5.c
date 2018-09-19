
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "libft.h"
#include "libssl.h"
#include "ft_ssl.h"
#include <stdio.h>

#define MD5HASHSIZE 16

static void	hash_stdin(t_sslparam *params)
{
	char	hash_str[MD5HASHSIZE * 2 + 1];
	char	*str;

	str = read_stdin();
	ft_memset(hash_str, 0, MD5HASHSIZE * 2 + 1);
	hash_to_str(hash_str, md5(str, ft_strlen(str)), MD5HASHSIZE);
	if (params->p)
		ft_printf("%s%s\n", str, hash_str);
	else
		ft_printf("%s\n", hash_str);
	free(str);
}

static int	hash_string(char *str, t_sslparam *opt)
{
	char	hash_str[MD5HASHSIZE * 2 + 1];

	ft_memset(hash_str, 0, MD5HASHSIZE * 2 + 1);
	hash_to_str(hash_str, md5(str, ft_strlen(str)), MD5HASHSIZE);
	if (opt->q)
		ft_printf("%s\n", hash_str);
	else if (opt->r)
		ft_printf("%s \"%s\"\n", hash_str, str);
	else
		ft_printf("MD5(\"%s\") = %s\n", str, hash_str);
	return (0);
}

static void	hash_file_print(uint8_t *hash_buff, char *file, t_sslparam *opt)
{
	char	hash_str[MD5HASHSIZE * 2 + 1];

	ft_memset(hash_str, 0, MD5HASHSIZE * 2 + 1);
	hash_to_str(hash_str, hash_buff, MD5HASHSIZE);
	if (opt->q)
		ft_printf("%s\n", hash_str);
	else if (opt->r)
		ft_printf("%s %s\n", hash_str, file);
	else
		ft_printf("MD5(%s) = %s\n", file, hash_str);
}

static int	hash_file(char *file, t_sslparam *opt)
{
	struct stat	st;
	void		*map;
	uint8_t		*buff;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1 || fstat(fd, &st) == -1)
	{
		error(file);
		return (1);
	}
	if (S_ISDIR(st.st_mode))
	{
		error_custom(file, "not a directory");
		close(fd);
		return (1);
	}
	map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
	buff = md5(map, st.st_size);
	hash_file_print(buff, file, opt);
	if (munmap(map, st.st_size) == -1 || close(fd) == -1)
	{
		error(file);
		return (1);
	}
	return (0);
}

int			ssl_md5(int argc, char **argv)
{
	t_sslparam	params;
	t_list		*last;
	int			ret;

	ret = 0;
	if (read_params(&params, argc, argv) == -1)
		return (1);
	if (params.p || (!params.strings && !params.files))
		hash_stdin(&params);
	last = params.strings;
	while (last)
	{
		ret += hash_string(last->content, &params);
		last = last->next;
	}
	ft_lstfreelist(&params.strings, free);
	last = params.files;
	while (last)
	{
		ret += hash_file(last->content, &params);
		last = last->next;
	}
	ft_lstfreelist(&params.files, free);
	return ((ret) ? 1 : 0);
}
