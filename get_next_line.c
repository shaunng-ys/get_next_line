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
	char	*line;
	//open(const char *path, int oflag, ...);
	//n would be file descriptor i.e. an integer used to uniquely identify an open file
	n = open("file.txt", O_RDONLY);
	FILE*	ptr = fopen("file.txt", "r");
	fseek(ptr, 0, SEEK_SET);
	line = get_next_line(n);
	while (line)
	{
		printf("This is supposed to be the line before new line: %s\n", line);
		free(line);
		line = get_next_line(n);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	//can sort of see how static n would be important for multiple gnl calls but somehow even on a single call, without making it static, it segfaults
	static char *leftover;
	size_t	n;
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
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

	count = 0;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	readvalue = 5;
	pl_index = 0;
	n = 0;
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
	//might be an issue where leftover is unitialised in the first instance/ iteration/ function call of gnl
	if (leftover != NULL)
	{
		if (strlen(leftover) > 0)
		//if (leftover[0])
		{
			printf("Now commencing operation: no character left behind! - Characters to be saved: %s\n", leftover);
			free(placeholder1);
			placeholder1 = ft_calloc(strlen(leftover) + 1, sizeof(char));
			while (count < strlen(leftover))
			{
				placeholder1[count] = leftover[count];
				count++;
			}
			printf("Characters that have been saved: %s\n", placeholder1);
			free(leftover);
		}
	}

	while (readvalue > 0)
	{
		/*
		if (strlen(leftover) > 0)
		{
			free(placeholder1);
			placeholder1 = ft_calloc(strlen(leftover) + 1, sizeof(char));
			while (count < strlen(leftover))
			{
				placeholder1[count] = leftover[count];
				count++;
			}
			free(leftover);
		}
		*/
		//read(int fildes, void *buf, size_t nbyte);
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue == 0)
			break;
		printf("This is in the buffer: %s & this is the rv: %d\n", (char *)buffer, readvalue);
		free(placeholder2);
		//need to account for leftover - to be done
		//what would happen in the instance where placeholder1 is empty, could this happen?
		placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
		//placeholder2 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1, 1);
		if (strlen(placeholder1) > 0)
		{
			while (placeholder1[pl_index])
			{
				placeholder2[pl_index] = placeholder1[pl_index];
				pl_index++;
				printf("loop1: placeholder1: %s, placeholder2: %s\n", placeholder1, placeholder2);
			}
			pl_index = 0;
			//printf("This is placeholder2: %s\n", placeholder2);//might need to reset the above 2 indices
		}
		free(placeholder1);
		//could this work?
		placeholder1 = ft_calloc(strlen(placeholder2) + BUFFER_SIZE + 1, 1);
		//placeholder1 = ft_calloc(BUFFER_SIZE + (BUFFER_SIZE * readiter) + 1, 1);
		if (strlen(placeholder2) > 0)
		{
			while (placeholder2[j])
			{
				placeholder1[j] = placeholder2[j];
				printf("loop2: placeholder2: %s, placeholder1: %s\n", placeholder2, placeholder1);
				j++;
			}
			j = 0;
		}
		while (((char *)buffer)[i])
		{
			placeholder1[n] = ((char *)buffer)[i];
			n++;
			i++;
		}
		i = 0;
		if (buffer_check(((char *)buffer), BUFFER_SIZE) > 0)	//meaning that there is a positive (found nl)
		{
			free(placeholder2);
			placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
			//placeholder2 = ft_calloc(BUFFER_SIZE * readiter + buffer_check((char *)buffer, BUFFER_SIZE), 1); 
			/*how many times read was successfully called till now + perhaps 1 or two for null terminating character etc.*/
	       		while (placeholder1[i] != '\n')
			{
			 	placeholder2[i] = placeholder1[i];
				i++;
			}
			placeholder2[i] = '\n';
			//to reset pointer such that we can use leftover for the next leftovers
			/*
			if (strlen(leftover) > 0)
				free(leftover);
			*/
			//to store the value of i so that it isn't lost (i is now the value after the newline character)
			l = ++i;
			//while l which is also same as i is not the null terminating character
			//this could be an issue where it's trying to read something not accessible such as a null terminating character
			//in which case I might need a character pointer which is set to after the \n and use strlen(that_pointer) as the condition for entering the loop
			while (placeholder1[l])
			{
				//k will be used to know how much to malloc/calloc
				k++;
				l++;
			}
			leftover = ft_calloc(k + 1, sizeof(char));
			//now that k is used, we can reset it to assign 
			k = 0;
			//this part is to assign the characters after nl for the next call of gnl (so that characters are not lost)
			while (placeholder1[i])
				leftover[k++] = placeholder1[i++];
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
