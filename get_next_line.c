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
	//n would be file descriptor i.e. an integer used to uniquely identify an open file
	n = open("multiple_line_no_nl.txt", O_RDONLY);
	FILE*	ptr = fopen("multiple_line_no_nl.txt", "r");
	fseek(ptr, 0, SEEK_SET);
	line = get_next_line(n);
	while (line)
	{
		printf("Line returned from gnl: %s\n", line);
		free(line);
		line = get_next_line(n);
	}
	return (0);
}




char	*get_next_line(int fd) //suck it alex, I'll name my variables how I like, you can name my balls
{
	static char *leftover;
	size_t	n;
	size_t	count;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;
	size_t	m;
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
	m = 0;
	readvalue = 5;
	pl_index = 0;
	n = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	
	placeholder1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	placeholder2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	//the line below is to guard against reads into the string where it isn't initialized, causing a segfault
	if (leftover != NULL) 
	{
		//printf("Passed the NULL condition because leftover != NULL\n\n");
		if (leftover[0] != '\0') //&& strlen(leftover) > 0) //|| *leftover != '\0')
		//if (strlen(leftover) > 0) //|| *leftover != '\0')
		//if (strlen(leftover) > 0)
		//if (leftover[0])
		{
			//printf("Operation no character left behind commencing! - Characters to be saved: %s\n", leftover);
			free(placeholder1);
			if (leftover[m] == '\n')
			{
				placeholder1 = ft_calloc(2/*strlen(leftover)*/, sizeof(char));
				placeholder1[count] = '\n';
				leftover++;
				return (placeholder1);
				//m++;
			}
			else
			{
				while (leftover[m] != '\n' && leftover[m])
					m++;
				placeholder1 = ft_calloc(m/*strlen(leftover)*/ + 2, sizeof(char));
				while (count < m)//strlen(leftover))
				{
					placeholder1[count] = leftover[count];
					count++;
				}
				if (leftover[m] == '\n')
				{
					placeholder1[count] = '\n';
					//printf("An attempt has been made to add a nl to the end of placeholder\n\n");
					//printf("This is the string in placeholder1 now: %s\n\n", placeholder1);
					leftover = leftover + m + 2;
					//printf("This is where leftover starts now (after nl): %c\n\n", leftover[0]);
					return (placeholder1);
				}
				else
				{
					leftover = leftover + m + 1;
					//printf("This is where leftover starts now: %c\n\n", leftover[0]);
				}
			}
			//printf("This is m, where m is the no. of chars before nl/ntc: %zu\n\n", m);
			//placeholder1 = ft_calloc(m/*strlen(leftover)*/ + 1, sizeof(char));
			//while (count < m)//strlen(leftover))
			//{
			//	placeholder1[count] = leftover[count];
			//	count++;
			//}
			//leftover = leftover + m;
			//printf("Character/s saved: %s\n", placeholder1);
			if	(leftover != NULL && leftover[0] == '\0')//&& strlen(placeholder1) < 1)
			//if	(strlen(placeholder1) < 1)
			{
				//printf("An attempt will now be made to free leftover\n");
				//free(leftover);
				//printf("Leftover is not NULL but starts with a ntc\n\n");//has been succcessfully freed!\n\n");
				leftover = NULL;
			}
			//wonder if leftover = NULL solves the issue (update: doesn't seem to)
			//leftover = NULL;
		}
		if	(leftover != NULL && leftover[0] == '\0')//&& strlen(placeholder1) < 1)
		//if	(strlen(placeholder1) < 1)
		{
			//printf("An attempt will now be made to free leftover\n");
			//free(leftover);
			//printf("Leftover is not NULL but starts with a ntc\n\n");//has been succcessfully freed!\n\n");
			leftover = NULL;
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
		//now my goal is to not read the buffer while leftover still has content and while placeholder still has content
		//if (strlen(leftover) < 1)
		readvalue = read(fd, buffer, BUFFER_SIZE);
		//printf("Read function used, readvalue = %d\n\n", readvalue);
		//printf("This is what's in the buffer now: %s\n\n", (char *)buffer);
		if (readvalue == 0 && strlen(placeholder1) > 0)
		{
			free(buffer);
			free(placeholder2);
			//free(leftover);
			//leftover = NULL;
			//printf("The EOF was found, read value is: %d, placeholder1 returned\n", readvalue);
			//printf("Placeholder1 is about to be returned from the gnl function\n\n");
			return (placeholder1);
		}
		else if (readvalue == 0 && leftover == NULL)//leftover[0] == '\0')
		{
			free(placeholder1);
			free(placeholder2);
			free(buffer);
			//leftover = NULL;
			//free(leftover);
			//printf("The EOF was found, read value is: %d, NULL returned\n", readvalue);
			//printf("NULL is about to be returned\n\n");
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
			//printf("Entered if statement because passed buffer check\n");
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
			if (placeholder1[l])
			{
				while (placeholder1[l])
				{
					//k will be used to know how much to malloc/calloc
					k++;
					l++;
				}
				//is the below condition necessary?
				//if (leftover == NULL)
					//free(leftover);
				//printf("Memory space for leftover is now needed\n\n");
				leftover = ft_calloc(k + 2, sizeof(char));
					//printf("leftover has been calloc'd via if statement #1, calloc'd char spaces = %zu\n", (k + 2));
				k = 0;
				while (placeholder1[i])
					leftover[k++] = placeholder1[i++];
				//printf("This is what's in leftover at this point: %s\n\n", leftover);
			}
			free(placeholder1);
			free(buffer);
			//printf("Placeholder2 is about to be returned\n\n");
			return (placeholder2);
	       	}
		/*
		else if (leftover[0] == '\0')
		{
			//printf("leftover will now be calloc'd and the pointer set to NULL\n");
			leftover = ft_calloc(2, sizeof(char));
			leftover = NULL;
			//printf("leftover should now be NULL\n");
		}
		*/
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

