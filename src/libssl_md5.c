
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "libssl.h"

#define FUNC_F(b,c,d) ((b) & (c)) | ((~(b)) & (d));
#define FUNC_G(b,c,d) ((d) & (b)) | ((~(d)) & (c));
#define FUNC_H(b,c,d) (b) ^ (c) ^ (d);
#define FUNC_I(b,c,d) (c) ^ ((b) | (~(d)));

#define A block[0]
#define B block[1]
#define C block[2]
#define D block[3]
#define F block[4]
#define G block[5]

static const uint32_t h[] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

static const uint32_t s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

static const uint32_t k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

#ifdef DEBUG
static void		debug_print_buff(uint8_t *buff, size_t len)
{
	size_t i;

	debug("len = %zu\n", len);
	i = -1;
	while (++i < len)
		debug(((i + 1) % 8 == 0) ? "%02x\n" : "%02x", buff[i]);
	debug("\n");
}
#endif

static uint32_t	transform(uint32_t i, uint32_t *block, uint32_t *m)
{
	if (i < 16)
	{
		F = FUNC_F(B, C, D);
		G = i;
	}
	else if (i < 32)
	{
		F = FUNC_G(B, C, D);
		G = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		F = FUNC_H(B, C, D);
		G = (3 * i + 5) % 16;
	}
	else
	{
		F = FUNC_I(B, C, D);
		G = (7 * i) % 16;
	}
	return (B + ROTATE(F + A + k[i] + m[G], s[i]));
}

static void		compress(char *msg, uint32_t *hash)
{
	uint32_t block[6];
	uint32_t i;
	uint32_t tmp;

	ft_memcpy(block, hash, sizeof(uint32_t) * 4);
	i = 0;
	while (i < 64)
	{
		tmp = transform(i, block, (uint32_t *)msg);
		A = D;
		D = C;
		C = B;
		B = tmp;
		debug("%#010x %#010x %#010x %#010x %#010x\n", A, B, C, D, F);
		++i;
	}
	i = -1;
	while (++i < 4)
		hash[i] += block[i];
}

static void		prepare_message_schedule(const void *msg, size_t len, \
						void **buff, size_t *bufflen)
{
#ifdef DEBUG
	debug_print_buff((uint8_t *)msg, len);
#endif
	*bufflen = len + 1;
	while (*bufflen % 64 != 56)
		++(*bufflen);
	*buff = malloc(*bufflen + sizeof(uint64_t));
	if (*buff == NULL)
	{
		perror("ft_ssl: sha256");
		exit(EXIT_FAILURE);
	}
	ft_memset(*buff, 0, *bufflen + sizeof(uint64_t));
	ft_memcpy(*buff, msg, len);
	*(uint32_t *)(*buff + len) = 0x80;
	*(uint32_t *)(*buff + *bufflen) = (uint32_t)(len * 8);
#ifdef DEBUG
	debug_print_buff((uint8_t *)*buff, *bufflen + sizeof(uint64_t));
#endif
}

void			*md5(const void *msg, size_t len)
{
	static uint32_t	hash[4];
	void			*buff;
	size_t			bufflen;
	size_t			i;

	ft_memcpy(hash, h, sizeof(uint32_t) * 4);
	prepare_message_schedule(msg, len, &buff, &bufflen);
	i = 0;
	while (i < bufflen)
	{
		compress(buff + i, hash);
		i += 64;
	}
	free(buff);
	return (&hash);
}
