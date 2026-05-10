#include "get_next_line.h"

char    *read_and_stash(int fd, char *stash)
{
    char    *buffer;
    char    *tmp;
    int     byte_read;

    byte_read = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    while ((!stash || !ft_strchr(stash, '\n')) && byte_read > 0)
    {
        byte_read = read(fd, buffer, BUFFER_SIZE);
        if (byte_read < 0)
        {
            free(buffer);
            free(stash);
            return (NULL);
        }
        buffer[byte_read] = '\0';
        tmp = ft_strjoin(stash, buffer);
        free(stash);
        stash = tmp;
    }
    free(buffer);
    return (stash);
}

char    *extract_line(char *stash)
{
    char    *newline;
    int     len;
    char    *line;
    int     i;

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

char    *update_stash(char *stash)
{
    char    *nextlinestart;
    char    *newstash;

    nextlinestart = ft_strchr(stash, '\n');
    if (!nextlinestart)
    {
        free(stash);
        return (NULL);
    }
    newstash = ft_strdup(nextlinestart + 1);
    free(stash);
    return (newstash);
}

char    *get_next_line(int fd)
{
    static char *stash;
    char        *line;

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


int main(void)
{
    int     fd;
    char    *line;

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
}