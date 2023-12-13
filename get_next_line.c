/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:59:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/13 19:09:06 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Cette fonction met a jour le cup_buffer apres appel a read et renvoie la taille prise
static int	read_from_fd(int fd, char **cup_buffer)
{
	int			bytes_read;

	*cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// CHECKER CETTE CONDITION
//	if (NULL == cup_buffer)
//		return (NULL);
	bytes_read = read(fd, *cup_buffer, BUFFER_SIZE);
	if (0 >= bytes_read)
		free(*cup_buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer = NULL;
	char		*cup_buffer;
//	char		*tmp;
	char		*line;
	int		l;

	if (BUFFER_SIZE <= 0 || fd <= 0)
		return (NULL);
//	if (!basin_buffer)
//		basin_buffer = ft_calloc(1, sizeof(char));
	while (!basin_buffer || !ft_strchr(basin_buffer, '\n'))
	{
		l = read_from_fd(fd, &cup_buffer);
		if (!l)
			return(free(basin_buffer), NULL);
		if (!basin_buffer)
			basin_buffer = cup_buffer;
		else
		{
			basin_buffer = ft_strjoin(&basin_buffer, cup_buffer);
			free (cup_buffer);
		}
//		free (basin_buffer);
//		basin_buffer = tmp;
	}
//	printf("stash before : %s\n", basin_buffer);
	line = extract_line(&basin_buffer);
//	printf("stash after : %s\n", basin_buffer);

	return (line);
}
/*
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
}*/
