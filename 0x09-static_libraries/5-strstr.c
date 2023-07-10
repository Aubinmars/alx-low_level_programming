#include "main.h"
#include <stddef.h>

/**
 * _strstr - locates a substring within a string
 * @haystack: the string to search in
 * @needle: the substring to find
 *
 * Return: a pointer to the beginning of the substring in the haystack,
 *         or NULL if the substring is not found.
 */
char *_strstr(char *haystack, char *needle)
{
	while (*haystack)
	{
		char *h = haystack;
		char *n = needle;

		while (*haystack && *n && *haystack == *n)
		{
			haystack++;
			n++;
		}

		if (!*n)
			return (h);

		haystack = h + 1;
	}

	return (NULL);
}
