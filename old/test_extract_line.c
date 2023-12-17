/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_extract_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjoyeux <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:53:24 by tjoyeux           #+#    #+#             */
/*   Updated: 2023/12/13 18:35:59 by tjoyeux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
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
/*
int	main(void)
{
	char	*stash;
	char	*line;

//	stash = ft_strdup("AAA\nBBB");
	stash = ft_strdup("AAA\nBBB\nCCC");
//	stash = ft_strdup("AAABBB");

	line = extract_line(&stash);
	printf("line : %s\n", line);
	printf("stash : %s\n", stash);
	free(line);
	free(stash);
}*/
