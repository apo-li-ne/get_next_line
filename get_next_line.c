/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: apolguil <apolguil@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2026/05/10 16:04:52 by apolguil	       #+#    #+#	      */
/*   Updated: 2026/05/10 16:11:06 by apolguil         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_and_free(char *stash, char *buffer)
{
	char	*tmp;

	tmp = ft_strjoin(stash, buffer);
	free(stash);
	return (tmp);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);

	byte_read = 1;
	while ((!stash || !ft_strchr(stash, '\n')) && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		stash = append_and_free(stash, buffer);
		if (!stash)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*newline;
	int		len;
	char	*line;
	int		i;

	i = 0;
	newline = ft_strchr(stash, '\n');
	if (newline)
		len = newline - stash + 1;
	else
		len = ft_strlen(stash);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	char	*nextlinestart;
	char	*newstash;

	nextlinestart = ft_strchr(stash, '\n');

	if (!nextlinestart)
	{
		free(stash);
		return (NULL);
	}

	if (*(nextlinestart + 1) == '\0')
	{
		free(stash);
		return (NULL);
	}

	newstash = ft_strdup(nextlinestart + 1);

	free(stash);

	return (newstash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	stash = update_stash(stash);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}*/
