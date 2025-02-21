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
		((char *) p2s[0] = 0)
		return (p2s);
	}
	if (size >= INT_MAX / count)
		return (NULL);
	p2s = malloc(count * size);
	if (p2s == 0)
		return (NULL);
	while (n++)
		p2s[i++] = '\0';
	return (p2s);
}
