//
//#include <stdlib.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//#include "libft.h"
//#include "libssl.h"
//#include "ft_ssl.h"
//#include <stdio.h>
//
//#define SHA256HASHSIZE 16
//
//#define a(x) (((x) > 9) ? ((x) + 'a' - 10) : ((x) + '0'))
//#define hash_string(str, opt) hash_msg(str, str, opt, 1)
//
//static void hash_print(uint8_t *hash, size_t len)
//{
//	size_t i;
//	char c;
//	i = 0;
//	while (i < len)
//	{
//		c = a(hash[i] / 16);
//		write(STDOUT_FILENO, &c, 1);
//		c = a(hash[i] % 16);
//		write(STDOUT_FILENO, &c, 1);
//		++i;
//	}
//}
//
//static int hash_msg(char *str, char *msg, t_sslopt *opt, int mode)
//{
//	uint8_t *buff;
//
//	buff = sha256(msg, ft_strlen(msg));
//	if (opt->q == 0 && opt->r == 0)
//		ft_printf((mode) ? "SHA256(\"%s\") = " : "MD%(%s)", str);
//	hash_print(buff, SHA256HASHSIZE);
//	if (opt->q == 0 && opt->r == 1)
//		ft_printf((mode) ? " \"%s\"" : " %s", str);
//	write(STDOUT_FILENO, "\n", 1);
//	return (0);
//}
//
////static int hash_file(char *file, t_sslopt *opt)
////{
////	struct stat filestat;
////	char *str;
////	int fd;
////
////	if (stat(file, &filestat) == -1 || (fd = open(file, O_RDONLY)) == -1)
////	{
////		error(file);
////		return (1);
////	}
////	if (!S_ISDIR(filestat.st_mode))
////	{
////		str = read_file(fd);
////		hash_msg(file, str, opt, 0);
////	}
////	else
////	{
////		error_custom(file, "not a directory");
////		return (1);
////	}
////	if (close(fd))
////	{
////		error(file);
////		return (1);
////	}
////	return (0);
////}
//
//int ssl_sha256(int argc, char **argv)
//{
//	t_sslopt opt;
//	size_t	 i;
//	size_t   j;
//	int		 ret;
//
//	ret = 0;
//	ft_memset(&opt, 0, sizeof(t_sslopt));
//	if ((j = read_params(&opt, argc, argv)) == (size_t)-1)
//		return (1);
//	i = 1;
//	while (i < (size_t)argc)
//	{
//		if (!ft_strcmp(argv[i], "-p") || !ft_strcmp(argv[i], "-q") || \
//			!ft_strcmp(argv[i], "-r"))
//			;
//		else if (!ft_strcmp(argv[i], "-s"))
//		{
//			ret += hash_string(argv[i], &opt);
//			++i;
//		}
//		else
//			; //ret += hash_file(argv[i], &opt);
//		++i;
//	}
//	return ((ret) ? 1 : 0);
//}
