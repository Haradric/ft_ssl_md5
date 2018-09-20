
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "libssl.h"

#define CH(x,y,z)    (((x) & (y)) ^ ((~(x)) & (z)))
#define MAJ(x,y,z)   (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define SIGMA_L0(x) (ROTATE((x),30) ^ ROTATE((x),19) ^ ROTATE((x),10))
# define SIGMA_L1(x) (ROTATE((x),26) ^ ROTATE((x),21) ^ ROTATE((x),7))
# define SIGMA_S0(x) (ROTATE((x),25) ^ ROTATE((x),14) ^ ((x)>>3))
# define SIGMA_S1(x) (ROTATE((x),15) ^ ROTATE((x),13) ^ ((x)>>10))

#define A  block[0]
#define B  block[1]
#define C  block[2]
#define D  block[3]
#define E  block[4]
#define F  block[5]
#define G  block[6]
#define H  block[7]
#define T1 block[8]
#define T2 block[9]

static const uint32_t h[] = {
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

static const uint32_t k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#ifdef DEBUG
static void		debug_print_buff(uint8_t *buff, size_t len)
{
	size_t	i;

	debug("len = %zu\n", len);
	i = -1;
	while (++i < len)
		debug(((i + 1) % 8 == 0) ? "%02x\n" : "%02x", buff[i]);
	debug("\n");
}
#endif

static void		reverse_bits_32_arr(uint32_t *arr, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		arr[i] = ((arr[i] & 0xff) << 24 | \
				(arr[i] & 0xff00) << 8 | \
				(arr[i] & 0xff0000) >> 8 | \
				(arr[i] & 0xff000000) >> 24);
		++i;
	}
}

static void		prepare_message_buffer(const void *message, size_t len, \
						uint32_t **buff, size_t *bufflen)
{
#ifdef DEBUG
	debug_print_buff((uint8_t *)message, len);
#endif
	size_t i = 0;

	while ((len * 8 + 1 + i) % 512 != 448)
		i++;
	*bufflen = (len * 8 + 1 + i + 64) / 8;
	*buff = malloc(*bufflen);
	if (*buff == NULL)
	{
		perror("ft_ssl: sha256");
		exit(EXIT_FAILURE);
	}
	ft_memset(*buff, 0, *bufflen);
	ft_memcpy(*buff, message, len);
	*((uint8_t *)(*buff) + len) = 0x80;
	reverse_bits_32_arr(*buff, *bufflen / 4);
	*(*buff + *bufflen / 4 - 1) = (uint32_t)(len * 8);
#ifdef DEBUG
	debug_print_buff((uint8_t *)*buff, *bufflen);
#endif
}

static void		prepare_message_schedule(uint32_t *message, uint32_t *w)
{
	size_t	i;

	i = 0;
	while (i < 16)
	{
		w[i] = message[i];
		++i;
	}
	while (i < 64)
	{
		w[i] = w[i - 16] + SIGMA_S0(w[i - 15]) + w[i - 7] + SIGMA_S1(w[i - 2]);
		++i;
	}
}

static void		compress(uint32_t *message, uint32_t *hash)
{
	uint32_t	block[10];
	uint32_t	w[64];
	uint32_t	i;

	ft_memcpy(block, hash, sizeof(uint32_t) * 8);
	prepare_message_schedule(message, &w[0]);
	i = -1;
	while(++i < 64)
	{
		T1 = H + SIGMA_L1(E) + CH(E, F, G) + k[i] + w[i];
		T2 = SIGMA_L0(A) + MAJ(A, B, C);
		H = G;
		G = F;
		F = E;
		E = D + T1;
		D = C;
		C = B;
		B = A;
		A = T1 + T2;
		debug("%#010x %#010x %#010x %#010x %#010x %#010x %#010x %#010x\n", \
				A, B, C, D, E, F, G, H);
	}
	i = -1;
	while (++i < 8)
		hash[i] += block[i];
}

void			*sha256(const void *msg, size_t len)
{
	static uint32_t	hash[8];
	uint32_t		*buff;
	size_t			bufflen;
	size_t			i;

	ft_memcpy(hash, h, sizeof(uint32_t) * 8);
	prepare_message_buffer(msg, len, &buff, &bufflen);
	i = 0;
	while (i < bufflen / 4)
	{
		compress(buff + i, hash);
		i += 16;
	}
	free(buff);
	reverse_bits_32_arr(hash, 8);
	return (&hash);
}
