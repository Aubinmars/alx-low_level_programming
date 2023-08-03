#include "main.h"

/**
 * binary_to_uint - converts a binary number to unsigned int
 * @b: string containing the binary number
 *
 * Return: the converted number, or 0 if an invalid character is found
 */
unsigned int binary_to_uint(const char *b)
{
	const char *ptr = b;
	unsigned int dec_val = 0;

	if (!b)
		return (0);

	/* Move the pointer to the end of the string */
	while (*ptr)
		ptr++;

	/* Start converting from the least significant digit */
	while (ptr != b)
	{
		ptr--; /* Move the pointer to the previous character */
		if (*ptr == '0' || *ptr == '1')
		{
			dec_val = (dec_val << 1) | (*ptr - '0');
		}
		else
		{
			/* Invalid character found */
			return (0);
		}
	}

	return (dec_val);
}
