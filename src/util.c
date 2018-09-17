
#include <stddef.h>
#include <stdint.h>

#define ASCII(x) (((x) > 9) ? ((x) + 'a' - 10) : ((x) + '0'))

void	hash_to_str(char *buff, uint8_t *hash, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	while (i < len)
	{
		buff[j] = ASCII(hash[i] / 16);
		buff[j + 1] = ASCII(hash[i] % 16);
		i += 1;
		j += 2;
	}
}
