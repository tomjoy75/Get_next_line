/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 23:29:59 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/13 18:41:24 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define INT_MAX 2147483647

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

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(1);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	if (nmemb > INT_MAX || size > INT_MAX || nmemb * size > INT_MAX)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr || !size)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
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

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
//	test_ptr((char *)s);
	while (s[i])
	{
		if (s[i] == c % 256)
			return ((char *)s + i);
		i++;
	}
	if (c == '\0')
		return ((char *)s + i);
	else
		return (NULL);
}
/*
void	*add_to_buffer(char *basin, char *add)
{
	char	*tmp_str;
	int	i;
	int	j;

	tmp_str = ft_calloc(ft_strlen(basin) + BUFFER_SIZE + 1, sizeof(char));
	if (!tmp_str)
		return (NULL);
	i = 0;
	j = 0;
	while (basin[i])
	{
		tmp_str[i] = basin[i];
		i++;
	}
	while (add[j])
	{
		tmp_str[i + j] = add[j];
		j++;
	}
	free (basin);
	free (add);
	return (tmp_str);
}*/
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
/*
char	*extract_line(char **stash)
{
	char	*line;
	char	*temp;
	int	i;
	int	j;

	i = 0;
	line = ft_calloc(ft_strlen(*stash) + 1, sizeof(char));
	if (!line)
		return (NULL);
	while ((*stash)[i] != '\n' && (*stash)[i])
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[i] = (*stash)[i];
	i++;
	j = 0;
	temp = ft_calloc(ft_strlen(*stash) - i, sizeof(char));
	if (!temp)
		return (line);
	while ((*stash)[i + j])
	{
		temp[j] = (*stash)[i + j];
		j++;
	}
	free(*stash);
	*stash = temp;
	//free (temp);
	return (line);
}*/

char	*extract_line(char **stash)
{
	char	*line;
	char	*remainder;
	char	*new_stash;
	int	i;
	
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

void	test_ptr(char *s)
{
	printf("\nAdresse : %p\nContenu : %s\n", s, s);
}
