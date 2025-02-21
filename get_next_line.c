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
	n = open("./text", O_RDONLY);
	get_next_line(n);
	return (0);
}

char	*get_next_line(int fd)
{
	static size_t	n;
	size_t	i;
	size_t	j;
	size_t	readiter;
	int	readvalue;
	size_t	index;
	void	*temp;
	void	*buffer;
	char	*placeholder1;
	size_t	p1_index;
	char	*placeholder2;
	size_t	p2_index;
	char	*ptr2line;

	i = 0;
	p1_index = 0;
	p2_index = 0;
	//this buffer is to store the read data from the read function call (but how much to malloc?)
	//use calloc heren
	index = BUFFER_SIZE;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	readvalue = read(fd, buffer, BUFFER_SIZE);
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
		readvalue = read(fd, buffer, BUFFER_SIZE); //set up for the next iteration of this while loop
		printf("This is the buffer's string: %s; & this is the rv: %zu\n", buffer, readvalue);
		free(placeholder2);
		placeholder2 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1);
		while (placeholder1[p1_index])
			placeholder2[p2_index++] = placeholder1[p1_index++];
		free(placeholder1);
		placeholder1 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1);
		while (buffer[i])
			placeholder1[p1_index++] = buffer[i++];
		i = 0;
		if (buffer_check(buffer) > 0);	//meaning that there is a positive (found nl)
		{
			free(placeholder2);
			placeholder2 = calloc(BUFFER_SIZE * readiter + buffer_check(buffer))/*how many times read was successfully called till now + perhaps 1 or two for null terminating character etc.*/)
	       		while (placeholder1[p1_index] != '\n')
			 	placeholder2[p2_index++] = placeholder1[p1_index++];
			return (placeholder2);
	       	}
		readiter++;
	}
	if (readvalue == 0)//Meaning EOF found
	{

	}
	//while loop to check buffer for nl or null terminating character, and creating line to be returned
	int	buffer_check(char *buffer)
	{
		while (index--)
		{
			if (buffer[i] == '\n')
			{	
				/*
				fp = ft_calloc(n + 2, sizeof(char));
				read(fd, fp, n);
				*/
				return (i + 2); //i + 1 maybe to indicate how many more to calloc for line that is to be returned
			}
			else
			{
				n++;
				i++;
			}
		}
		return (0);
	}
	return ((char *)fp);
}
