#include <stdio.h>
#include <sys/errno.h>
#include <stdlib.h>

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("malloc");
		exit(errno);
	}
	return (ptr);
}

void    vector_debug(char **vector)
{
    int i;

    i = 0;
    while (vector[i])
    {
        printf("%s\n", vector[i]);
        i++;
    }
}