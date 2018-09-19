
#ifndef LIBSSL_H
#define LIBSSL_H

# include <stdlib.h>

# ifdef DEBUG
# include <stdio.h>
#  define debug(...) do \
{ \
printf(__VA_ARGS__); \
fflush(stdout); \
} while (0)
# else
#  define debug(...)
# endif

/*
** Left rotate
*/
#define ROTATE(x,n) (((x) << (n)) | ((x) >> (32 - (n))))

void	*md5(const void *msg, size_t len);
void	*sha256(const void *msg, size_t len);

#endif
