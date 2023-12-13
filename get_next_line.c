/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:59:18 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/13 23:52:53 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char **s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!(*s1) || !s2)
		return (NULL);
	s3 = ft_calloc(ft_strlen(*s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
		return (NULL);
	i = 0;
	while ((*s1)[i])
	{
		s3[i] = (*s1)[i];
		i++;
	}
	free(*s1);
	j = 0;
	while (s2[j])
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	return (s3);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*remainder;
	char	*new_stash;
	int		i;

	remainder = ft_strchr(*stash, '\n');
	if (!remainder)
	{
		line = *stash;
		*stash = NULL;
		return (line);
	}
	remainder++;
	line = ft_calloc((remainder - *stash + 1), sizeof(char)); 
	i = 0;
	while ((*stash + i) < remainder)
	{
		line[i] = (*stash)[i]; 
		i++;
	}
	new_stash = ft_strdup(remainder);
	free(*stash);
	*stash = new_stash;
	return (line);
}

static int	read_from_fd(int fd, char **cup_buffer)
{
	int			bytes_read;

	*cup_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (NULL == *cup_buffer)
		return (0);
	bytes_read = read(fd, *cup_buffer, BUFFER_SIZE);
	if (0 >= bytes_read)
		free(*cup_buffer);
	return (bytes_read);
}

char	*get_next_line(int fd)
{
	static char	*basin_buffer = NULL;
	char		*cup_buffer;
	char		*line;
	int			l;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (!basin_buffer || !ft_strchr(basin_buffer, '\n'))
	{
		l = read_from_fd(fd, &cup_buffer);
		if (l <= 0)
			return (free(basin_buffer), NULL);
		if (!basin_buffer)
			basin_buffer = cup_buffer;
		else
		{
			basin_buffer = ft_strjoin(&basin_buffer, cup_buffer);
			free (cup_buffer);
		}
	}
	line = extract_line(&basin_buffer);
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
