/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shaun <sng@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 21:57:19 by shaun             #+#    #+#             */
/*   Updated: 2025/02/15 21:57:21 by shaun             ###   ########kl       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
//# define BUFFER_SIZE

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h> //Don't include this! Just for testing purposes
# include <limits.h>
# include <string.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t count, size_t size);
int	buffer_check(char *buffer, size_t index);

#endif
