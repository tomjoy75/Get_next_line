/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_medium.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:58:06 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/16 18:00:24 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define BUFFER_SIZE 5 

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char **s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!(*s1) || !s2)
		return (NULL);
	s3 = malloc((ft_strlen(*s1) + ft_strlen(s2) + 1) * sizeof(char));
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

char	*read_from_fd(int fd, char **stash)
{
	char	*cup_buffer;
	int		bytes_read;

	if (!(*stash))
		*stash = ft_strdup("");
	cup_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!cup_buffer)
		return (free(stash), NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if ((*stash)[0] == '\0' && !bytes_read)
		return (free(*stash), free(cup_buffer), NULL);
	if (bytes_read < 0)
		return (free(*stash), free(cup_buffer), NULL);
	cup_buffer[bytes_read] = '\0';
	while (bytes_read > 0)
	{
		*stash = ft_strjoin(stash, cup_buffer);
		if (!(*stash))
			return (free(*stash), free(cup_buffer), NULL);
		bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(*stash), free(cup_buffer), NULL);
		cup_buffer[bytes_read] = '\0';
	}
	return (free(cup_buffer), *stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	// Cas de bases

	// Creer stash
	stash = read_from_fd(fd, &stash);
	if (!stash)
		return (NULL);
	// Extract stash
	line = ft_strdup(stash);
	free(stash);
	stash = NULL;
	return (line);
}
/*
#include <fcntl.h>
int	main(int argc, char **argv)
{
	int	fd;
	char	*next_line;
	int	count;

	if (argc < 2)
		return (1);
	count = 0;
	fd = open(argv[1], O_RDONLY);
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
