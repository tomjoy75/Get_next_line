/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:59:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/08 15:29:53 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*read_from_fd(int fd)
{
	int			bytes_read;
	char		*cup_buffer;
	static int	count = 1;

	printf("ft_calloc#[%d]---", count++);
	cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (NULL == cup_buffer)
		return (NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (0 >= bytes_read)
		return (free(cup_buffer), NULL);
	return (cup_buffer);
}

char	*get_next_line(int fd)
{
	char	*basin_buffer;

	basin_buffer = read_from_fd(fd);
	return (basin_buffer);
}

#include <fcntl.h>
int	main(void)
{
	int	fd;
	char	*next_line;
	int	count;

	count = 0;
	fd = open("example.txt", O_RDONLY);
	if (0 >= fd)
		return (1);
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break;
		count++;
		printf("[%d]:%s\n", count, next_line);
		free(next_line);
	}
	close(fd);
	return (0);
}
