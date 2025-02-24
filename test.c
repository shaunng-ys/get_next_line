#include "get_next_line.h"

int	main(void)
{
	size_t	n;
	int	rv;
	char	*buffer;
	//open(const char *path, int oflag, ...);
	//n would be file descriptor i.e. an integer used to uniquely identify an open file
	n = open("file.txt", O_RDONLY);
	rv = 5;
	FILE*	ptr = fopen("file.txt", "r");
	buffer = calloc(21, sizeof(char));

	fseek(ptr, 0, SEEK_SET);
	while (rv > 0)
	{
		rv = read(n, buffer, 5);
		if (rv == 0)
		{
			printf("This is the return value of read: %d\n", rv);
			break;
		}
		printf("This is the buffer content: %s, This is the return value of read: %d\n", buffer, rv);
	}
	/*
	rv = read(n, buffer, 5);
	printf("This is the buffer content: %s, This is the return value of read: %d\n", buffer, rv);
	rv = read(n, buffer, 5);
	printf("This is the buffer content: %s, This is the return value of read: %d\n", buffer, rv);
	rv = read(n, buffer, 5);
	printf("This is the buffer content: %s, This is the return value of read: %d\n", buffer, rv);
	*/
	return (0);
}
