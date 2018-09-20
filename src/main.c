
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_ssl.h"

#define INPUT_SIZE 1024

static int	from_stdin(const t_sslfunc *func_arr)
{
	(void)func_arr;
	terminate_custom("ft_ssl", NULL, "read from stdin is not implemented yet");
	return (1);
}

static int	from_argv(const t_sslfunc *func_arr, int argc, char **argv)
{
	size_t i;

	i = 0;
	while (i < SSLFUNCNUM)
	{
		if (!ft_strcmp(argv[1], func_arr[i].name))
			return (func_arr[i].func(argc - 1, &argv[1]));
		++i;
	}
	terminate_custom("ft_ssl", argv[1], "invalid command");
	return (1);
}

int			main(int argc, char **argv)
{
	const t_sslfunc arr[SSLFUNCNUM] = {
		{"md5", ssl_md5},
		{"sha256", ssl_sha256}
	};

#ifdef DEBUG
	sleep(1);
#endif
	if (argc == 1)
		from_stdin(arr);
	else
		from_argv(arr, argc, argv);
	return (0);
}
