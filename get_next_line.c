char    *read_and_stash(int fd, char *stash)
{
    char    *buffer;
    char    *tmp;
    int     byte_read;

    byte_read = 1;
    buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buffer)
        return (NULL);
    while ((!stash ||!strchr(stash, '\n')) && byte_read > 0)
    {
        byte_read = read(fd, buffer, BUFFER_SIZE);
        if (byte_read < 0)
        {
            free(buffer);
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
    newline = strchr(stash, '\n');  
    len = newline - stash + 1;

    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);
    while (newline && i < len)
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
    
    nextlinestart = strchr(stash, '\n');
    newstash = ft_strdup(nextlinestart + 1);
    free(stash);
    return (newstash);
}

char    *get_next_line(int fd)
{
    static char     *stash;
    char    *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stash = read_and_stash(fd, stash);
    if (!stash)
        return (NULL);
    line = extract_line(stash);
    stash = update_stash(stash);
    return (line);
}