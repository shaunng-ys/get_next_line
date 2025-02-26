/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:56:54 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:56:56 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p2s;
	size_t	n;
	size_t	i;

	i = 0;
	n = (count * size);
	if (count == 0 || size == 0)
	{
		p2s = malloc(1);
		(((char *)p2s)[0] = 0);
		return (p2s);
	}
	if (size >= INT_MAX / count)
		return (NULL);
	p2s = malloc(count * size);
	if (p2s == 0)
		return (NULL);
	while (n)
	{
		((char *)p2s)[i++] = '\0';
		n--;
	}
	return (p2s);
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
