
#ifndef FT_SSL_H
# define FT_SSL_H

# define SSLFUNCNUM     2
# define SSLFUNCNAMELEN 16

typedef struct	s_sslfunc {
	char		name[SSLFUNCNAMELEN];
	int			(*func)(int argc, char **argv);
}				t_sslfunc;

typedef struct	s_sslparam {
	uint8_t		p:1;
	uint8_t		q:1;
	uint8_t		r:1;
	uint8_t		s:1;
	t_list		*strings;
	t_list		*files;
}				t_sslparam;

int				ssl_md5(int argc, char **argv);
int				ssl_sha256(int argc, char **argv);

int				read_params(t_sslparam *opt, int argc, char **argv);
char			*read_stdin(void);
char			*read_file(char *path, int fd, size_t len);

void			error(const char *prefix, const char *str);
void			terminate(const char *prefix, const char *str);
void			error_custom(const char *prefix, const char *str, \
						const char *err_str);
void			terminate_custom(const char *prefix, const char *str, \
						const char *err_str);

void			hash_to_str(char *buff, uint8_t *hash, size_t len);

#endif
