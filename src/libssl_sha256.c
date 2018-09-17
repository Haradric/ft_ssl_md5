
#include "libft.h"
#include "libssl.h"

#define ROT_R(x,n) (((x) >> (n)) | ((x) << (32 - (n))))

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
	size_t i;

	debug("len = %zu\n", len);
	i = -1;
	while (++i < len)
		debug(((i + 1) % 8 == 0) ? "%02x\n" : "%02x", buff[i]);
	debug("\n");
}
#endif

static void		compress(uint32_t i, uint32_t *block, uint32_t *w)
{
	uint32_t s0;
	uint32_t s1;

	s1 = ROT_R(E, 6) ^ ROT_R(E, 11) ^ ROT_R(E, 25);
	T1 = H + s1 + (E & F) ^ ((~E) & G) + k[i] + w[i];
	s0 = ROT_R(A, 2) ^ ROT_R(A, 13) ^ ROT_R(A, 22);
	T2 = s0 + (A & B) ^ (A & C) ^ (B & C);
}

static void		extend_chunk(void *msg, uint32_t *w)
{
	size_t	i;
	uint32_t s0;
	uint32_t s1;

	ft_memcpy(w, msg, sizeof(uint32_t) * 16);
	i = 15;
	while (i < 64)
	{
		s0 = ROT_R(w[i - 15], 7) ^ ROT_R(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = ROT_R(w[i - 2], 17) ^ ROT_R(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		++i;
	}
}

static void		process_chunk(char *msg, uint32_t *hash)
{
	uint32_t	block[10];
	uint32_t	w[64];
	uint32_t	i;

	ft_memcpy(block, hash, sizeof(uint32_t) * 8);
	extend_chunk(msg, (uint32_t *)&w);
	i = 0;
	while(i < 64)
	{
		compress(i, block, (uint32_t *)&w);
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
		++i;
	}
	i = -1;
	while (++i < 8)
		hash[i] += block[i];
}

static void		init_msg_buff(const void *msg, size_t len, void **buff, size_t *bufflen)
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
		perror("ft_ssl");
		exit(EXIT_FAILURE);
	}
	ft_memset(*buff, 0, *bufflen + sizeof(uint64_t));
	ft_memcpy(*buff, msg, len);
	*(uint32_t *)(*buff + len) = 0x01;
	*(uint32_t *)(*buff + *bufflen) = (uint32_t)(len * 8);
#ifdef DEBUG
	debug_print_buff((uint8_t *)*buff, *bufflen + sizeof(uint64_t));
#endif
}

void			*sha256(const void *msg, size_t len)
{
	static uint32_t	hash[8];
	void			*buff;
	size_t			bufflen;
	size_t			i;

	ft_memcpy(hash, h, sizeof(uint32_t) * 8);
	init_msg_buff(msg, len, &buff, &bufflen);
	debug("    A          B          C          D          E          F\
          G          H\n");
	i = 0;
	while (i < bufflen)
	{
		process_chunk(buff + i, hash);
		i += 64;
	}
	free(buff);
	return (&hash);
}
