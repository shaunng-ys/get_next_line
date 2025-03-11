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
*/

char	*get_next_line(int fd)
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

	//The entire if statement below is to take care of any leftovers past the new line on the previous gnl call
	if (leftover != NULL) 
	{
		if (leftover[0] != '\0') 
		{
			free(placeholder1);
			if (leftover[m] == '\n')
			{
				placeholder1 = ft_calloc(2, sizeof(char));
				placeholder1[count] = '\n';
				/*
				the problem with incrementing leftover's pointer is that it creates a memory leak because
				the characters moved past are "lost"
				*/
				//leftover++;
				//the lines below are a potential solution to my leftover issue
				free(placeholder2);
				placeholder2 = ft_calloc(strlen(leftover), sizeof(char));
				while(leftover[++i])
					placeholder2[j++] = leftover[i];
				i = 0;
				j = 0;
				free(leftover);
				leftover = ft_calloc(strlen(placeholder2) + 1, sizeof(char));
				while(placeholder2[j])
				{
					leftover[j] = placeholder2[j];
					j++;
				}
				free(placeholder2);
				free(buffer);
				return (placeholder1);
			}
			else
			{
				while (leftover[m] != '\n' && leftover[m])
					m++;
				placeholder1 = ft_calloc(m + 2, sizeof(char));
				while (count < m)
				{
					placeholder1[count] = leftover[count];
					count++;
				}
				if (leftover[m] == '\n')
				{
					placeholder1[count] = '\n';
					//the lines from here on are a potential solution to the leftover memory leak
					free(placeholder2);
					//from here on till the end of the if statement, my indexing might be off so trial and error
					placeholder2 = ft_calloc(strlen(leftover) - m + 1, sizeof(char));
					while(leftover[++m])
						placeholder2[i++] = leftover[m];
					i = 0;
					free(leftover);
					leftover = ft_calloc(strlen(placeholder2) + 1, sizeof(char));
					while(placeholder2[j])
					{
						leftover[j] = placeholder2[j];
						j++;
					}
					j = 0;
					//leftover = leftover + m + 1;
					free(buffer);
					return (placeholder1);
				}
				else
				{
					//leftover = leftover + m + 1;
					free(leftover);
					//leftover = ft_calloc(1, sizeof(char));
					leftover = NULL;
				}
			}
			if (leftover != NULL && leftover[0] == '\0')
				leftover = NULL;
		}
		if (leftover != NULL && leftover[0] == '\0')
			leftover = NULL;
	}
	/*
	The entire bottom half this point on is meant to place buffers inside a memory space
	& stack them until a new line or null terminating character is found
	*/
	i = 0;
	j = 0;
	while (readvalue > 0)
	{
		if (strlen(buffer) > 0)
		{
			free(buffer);
			buffer = ft_calloc(BUFFER_SIZE + 1, 1);
		}
		//what happens if you call read again after EOF is found? Ans: 0 continues to be returned
		readvalue = read(fd, buffer, BUFFER_SIZE);
		/*
		the if statement below should execute if there's nothing left to read from the file
	    	and leftover (until nl or ntc) was passed into placeholder1
		*/
		if (readvalue == 0 && strlen(placeholder1) > 0)
		{
			free(buffer);
			free(placeholder2);
			return (placeholder1);
		}
		/*
		the if statement below should pass if there's nothing left in the file to read
		& leftover has been fully passed through
		*/
		else if (readvalue == 0 && leftover == NULL)//leftover[0] == '\0')
		{
			free(placeholder1);
			free(placeholder2);
			free(buffer);
			return (NULL);
		}
		free(placeholder2);
		placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
		/*
		this part below is to keep a backup of placeholder1 (if not empty)
		so that I can increase the size of placeholder1 new buffers
		*/
		if (strlen(placeholder1) > 0)
		{
			while (placeholder1[pl_index])
			{
				placeholder2[pl_index] = placeholder1[pl_index];
				pl_index++;
			}
			pl_index = 0;
		}
		free(placeholder1);
		placeholder1 = ft_calloc(strlen(placeholder2) + BUFFER_SIZE + 1, 1);
		/*
		this part below is for getting back whatever was backed up in placeholder2
		from placeholder1 and add to that new buffers
		*/
		if (strlen(placeholder2) > 0)
		{
			while (placeholder2[j])
			{
				placeholder1[j] = placeholder2[j];
				j++;
			}
			j = 0;
		}
		n = strlen(placeholder2);
		// if (i != 0)
		// 	i = 0;
		while (((char *)buffer)[i])
		{	
			placeholder1[n] = ((char *)buffer)[i];
			n++;
			i++;
		}
		i = 0;
		/*
		this part below is to check the buffer for a nl, and where found, return everything
		until and including that nl
		*/
		if (buffer_check(((char *)buffer), BUFFER_SIZE) > 0)
		{
			free(placeholder2);
			placeholder2 = ft_calloc(strlen(placeholder1) + 1, 1);
			while (placeholder1[i] != '\n')
			{
			 	placeholder2[i] = placeholder1[i];
				i++;
			}
			placeholder2[i] = '\n';
			l = ++i;
			/*
			this part below is to check for anything after the nl and pass that (if found)
			into the static character pointer
			*/
			if (placeholder1[l])
			{
				while (placeholder1[l])
				{
					k++;
					l++;
				}
				leftover = ft_calloc(k + 2, sizeof(char));
				k = 0;
				while (placeholder1[i])
					leftover[k++] = placeholder1[i++];
			}
			free(placeholder1);
			free(buffer);
			return (placeholder2);
	    }
	}
	free(placeholder1);
	free(placeholder2);
	free(buffer);
	return (NULL);
}

