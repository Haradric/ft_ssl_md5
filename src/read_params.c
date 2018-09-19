
#include <unistd.h>
#include "libft.h"
#include "ft_ssl.h"

static int	read_flags(int i, int argc, char **argv, t_sslparam *opt)
{
	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-p"))
			opt->p = 1;
		else if (!ft_strcmp(argv[i], "-q"))
			opt->q = 1;
		else if (!ft_strcmp(argv[i], "-r"))
			opt->r = 1;
		else if (!ft_strcmp(argv[i], "-s") || argv[i][0] != '-')
			break ;
		else
		{
			write(STDERR_FILENO, "ft_ssl: md5: '", 14);
			write(STDERR_FILENO, argv[i], ft_strlen(argv[i]));
			write(STDERR_FILENO, "' unknown option\n", 17);
			return (-1);
		}
		++i;
	}
	return (i);
}

static int	read_strings(int i, int argc, char **argv, t_sslparam *opt)
{

	while (i < argc)
	{
		if (!ft_strcmp(argv[i], "-s"))
		{
			++i;
			ft_lstpushback(&opt->strings, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		}
		else
			break ;
		++i;
	}
	return (i);
}

static int	read_files(int i, int argc, char **argv, t_sslparam *opt)
{
	while (i < argc)
	{
		ft_lstpushback(&opt->files, ft_lstnew(argv[i], ft_strlen(argv[i]) + 1));
		++i;
	}
	return (i);
}

int			read_params(t_sslparam *opt, int argc, char **argv)
{
	int		i;

	ft_memset(opt, 0, sizeof(*opt));
	i = 1;
	if ((i = read_flags(i, argc, argv, opt)) == -1)
		return (-1);
	i = read_strings(i, argc, argv, opt);
	i = read_files(i, argc, argv, opt);
	return (i);
}
