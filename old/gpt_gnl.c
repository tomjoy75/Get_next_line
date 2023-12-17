#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define BUFFER_SIZE 5 

char	*strjoin(char **s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!(*s1) || !s2)
		return (NULL);
	s3 = calloc(strlen(*s1) + strlen(s2) + 1, sizeof(char));
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

// Ajoutez cette fonction pour vérifier et couper la ligne au saut de ligne
char *cut_line(char **stash) {
    char *line;
    char *temp;
    int i;

    i = 0;
    while ((*stash)[i] && (*stash)[i] != '\n')
        i++;

    if ((*stash)[i] == '\n') {
        line = strndup(*stash, i + 1); // Utilisez strndup pour copier la ligne jusqu'au '\n' inclus
        temp = strdup(&((*stash)[i + 1])); // Copiez le reste dans temp
        free(*stash);
        *stash = temp;
        return line;
    } else {
        line = strdup(*stash);
        free(*stash);
        *stash = NULL;
        return line;
    }
}

char *get_next_line(int fd) {
    static char *stash = NULL;
    char cup_buffer[BUFFER_SIZE + 1];
    int bytes_read;
    char *temp;

    if (!stash)
        stash = strdup("");

    while ((bytes_read = read(fd, cup_buffer, BUFFER_SIZE)) > 0) {
        cup_buffer[bytes_read] = '\0';
        temp = strjoin(&stash, cup_buffer); // Concaténez stash et cup_buffer
        free(stash);
        stash = temp;
        if (strchr(cup_buffer, '\n')) // Vérifiez si cup_buffer contient '\n'
            break;
    }

    if (bytes_read < 0)
        return NULL;

    if (bytes_read == 0 && stash[0] == '\0') {
        free(stash);
        stash = NULL;
        return NULL;
    }

    return cut_line(&stash);
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
