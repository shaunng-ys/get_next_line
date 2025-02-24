/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:56:36 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:56:38 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	size_t	n;
	//open(const char *path, int oflag, ...);
	//n would be file descriptor i.e. an integer used to uniquely identify an open file
	n = open("file.txt", O_RDONLY);
	FILE*	ptr = fopen("file.txt", "r");
	fseek(ptr, 0, SEEK_SET);
	printf("This is supposed to be the line before new line: %s\n", get_next_line(n));
	return (0);
}

char	*get_next_line(int fd)
{
	//can sort of see how static n would be important for multiple gnl calls but somehow even on a single call, without making it static, it segfaults
	static size_t	n;
	size_t	i;
	size_t	j;
	size_t	readiter;
	int	readvalue;
	size_t	index;
	void	*temp;
	void	*buffer;
	char	*placeholder1;
	size_t	pl_index;
	char	*placeholder2;
	//size_t	p2_index;
	char	*ptr2line;

	i = 0;
	j = 0;
	readvalue = 5;
	pl_index = 0;
	//p2_index = 0;
	//this buffer is to store the read data from the read function call (but how much to malloc?)
	//use calloc heren
	index = BUFFER_SIZE;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	
	placeholder1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	placeholder2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	/*
	The operating system keeps track of the "current position" in the file. 
	When you open the file, this will be the start of the file. 
	Every time you call read, you read some bytes from the current position, and also advance the current position.
	You can use lseek to change the current position.
	*/
	while (readvalue > 0)
	{
		//read(int fildes, void *buf, size_t nbyte);
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue == 0)
			break;
		printf("This is the buffer's string: %s; & this is the rv: %d\n", (char *)buffer, readvalue);
		free(placeholder2);
		placeholder2 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1, 1);
		if (strlen(placeholder1) > 0)
		{
			while (placeholder1[pl_index])
			{
				placeholder2[pl_index] = placeholder1[pl_index];
				pl_index++;
				printf("loop1\n");
			}
			pl_index = 0;
			printf("This is placeholder2: %s\n", placeholder2);//might need to reset the above 2 indices
		}
		free(placeholder1);
		placeholder1 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1, 1);
		if (strlen(placeholder2) > 0)
		{
			while (placeholder2[j])
			{
				placeholder1[j] = placeholder2[j];
				printf("loop2\n");
				j++;
			}
			j = 0;
		}
		while (((char *)buffer)[i])
		{
			placeholder1[n++] = ((char *)buffer)[i];
			i++;
		}
		i = 0;
		if (buffer_check(((char *)buffer), BUFFER_SIZE) > 0)	//meaning that there is a positive (found nl)
		{
			free(placeholder2);
			placeholder2 = ft_calloc(BUFFER_SIZE * readiter + buffer_check((char *)buffer, BUFFER_SIZE), 1); 
			/*how many times read was successfully called till now + perhaps 1 or two for null terminating character etc.*/
	       		while (placeholder1[i] != '\n')
			{
			 	placeholder2[i] = placeholder1[i];
				i++;
			}
			placeholder2[i] = '\n';
	       		return (placeholder2);
	       	}
		readiter++;
	}
	if (buffer_check(((char *)buffer), BUFFER_SIZE) == 0)
	{	
		return (placeholder1);
	//if (readvalue == 0)//Meaning EOF found
		printf("The EOF was found, read value is 0: %d\n", readvalue);
	}
}

//while loop to check buffer for nl or null terminating character, and creating line to be returned
int	buffer_check(char *buffer, size_t index)
{
	size_t	i;
	//size_t	n;

	i = 0;
	//n = 0;
	while (index--)
	{
		if (((char *)buffer)[i] == '\n')
		{	
			/*
			fp = ft_calloc(n + 2, sizeof(char));
			read(fd, fp, n);
			*/
			return (i + 2); //i + 1 maybe to indicate how many more to calloc for line that is to be returned
		}
		else
		{
			//n++;
			i++;
		}
	}
	return (0);
}
