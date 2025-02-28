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

/*
int	main(void)
{
	size_t	n;
	char	*line;
	//n would be file descriptor i.e. an integer used to uniquely identify an open file
	n = open("tester.txt", O_RDONLY);
	FILE*	ptr = fopen("tester.txt", "r");
	fseek(ptr, 0, SEEK_SET);
	line = get_next_line(n);
	while (line)
	{
		//printf("Line returned from gnl: %s\n", line);
		free(line);
		line = get_next_line(n);
	}
	return (0);
}
*/


char	*get_next_line(int fd) //suck it alex, I'll name my variables how I like, you can name my balls
{
	static char *leftover;
	size_t	n;
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	int	readvalue;
	void	*buffer;
	char	*placeholder1;
	size_t	pl_index;
	char	*placeholder2;

	count = 0;
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	readvalue = 5;
	pl_index = 0;
	n = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	
	placeholder1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	placeholder2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (leftover != NULL) //|| *leftover != '\0')
	{
		if (strlen(leftover) > 0)
		//if (leftover[0])
		{
			//printf("Operation no character left behind commencing! - Characters to be saved: %s\n", leftover);
			free(placeholder1);
			placeholder1 = ft_calloc(strlen(leftover) + 1, sizeof(char));
			while (count < strlen(leftover))
			{
				placeholder1[count] = leftover[count];
				count++;
			}
			//printf("Character/s saved: %s\n", placeholder1);
			//printf("An attempt will now be made to free leftover\n");
			free(leftover);
			//printf("Leftover has been succcessfully freed!\n");
		}
	}
	while (readvalue > 0)
	{
		if (strlen(buffer) > 0)
		{
			free(buffer);
			buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		}
		//read(int fildes, void *buf, size_t nbyte);
		readvalue = read(fd, buffer, BUFFER_SIZE);
		if (readvalue == 0 && strlen(placeholder1) > 0)
			return (placeholder1);
			//printf("The EOF was found, read value is: %d\n", readvalue);
		if (readvalue == 0)
		{
			free(placeholder1);
			free(placeholder2);
			free(buffer);
			return (NULL);
		}
		free(placeholder2);
		placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
		//moving the line directly below from the if conditional below fixed the issue, but why?
		//this is a condition that might not have been met, potentially causing a problem with the attempted calloc 12 lines below
		if (strlen(placeholder1) > 0)
		{
			//placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
			while (placeholder1[pl_index])
			{
				placeholder2[pl_index] = placeholder1[pl_index];
				pl_index++;
			}
			pl_index = 0;
		}
		free(placeholder1);
		//there might be an issue here if placeholder2 is freed
		placeholder1 = ft_calloc(strlen(placeholder2) + BUFFER_SIZE + 1, 1);
		if (strlen(placeholder2) > 0)
		{
			while (placeholder2[j])
			{
				placeholder1[j] = placeholder2[j];
				j++;
			}
			j = 0;
		}
		//n is now the index after the initial characters from previous iterations of the loop
		n = strlen(placeholder2);
		while (((char *)buffer)[i])
		{	
			placeholder1[n] = ((char *)buffer)[i];
			n++;
			i++;
		}
		i = 0;
		//printf("This is placeholder1: %s\n", placeholder1);
		if (buffer_check(((char *)buffer), BUFFER_SIZE) > 0)	//meaning that there is a positive (found nl)
		{
			free(placeholder2);
			placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
	       		while (placeholder1[i] != '\n')
			{
			 	placeholder2[i] = placeholder1[i];
				i++;
			}
			placeholder2[i] = '\n';
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
			k = 0;
			while (placeholder1[i])
				leftover[k++] = placeholder1[i++];
			free(placeholder1);
			free(buffer);
			return (placeholder2);
	       	}
	}
	return (NULL);
	/*
	if (buffer_check(((char *)buffer), BUFFER_SIZE) == 0)
	{	
		printf("The EOF was found, read value is 0: %d\n", readvalue);
		return (NULL);
	//if (readvalue == 0)//Meaning EOF found
	}
	*/
}

