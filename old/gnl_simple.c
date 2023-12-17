/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_gnl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 12:58:06 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/15 17:50:22 by tjoyeux          ###   ########.fr       */
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

char	*read_from_fd(int fd)
{
	char	*cup_buffer;
//	char	*stash;
	int		bytes_read;

	cup_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!cup_buffer)
		return (NULL);
	bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free(cup_buffer), NULL);
	cup_buffer[bytes_read] = '\0';
//	stash = ft_strdup(cup_buffer);
	return(cup_buffer);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*cup_buffer;
	char 		*line;

	cup_buffer = read_from_fd(fd);
	if (!cup_buffer)
		return (NULL);
	stash = ft_strdup(cup_buffer);
	free(cup_buffer);
	line = ft_strdup(stash);
	return (free(stash), line);
}

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
}
