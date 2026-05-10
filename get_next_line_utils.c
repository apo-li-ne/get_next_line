#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*cat;
	size_t			len;

	i = 0;
	j = 0;

	if (!s2)
    return (NULL);
    if (!s1)
    return (ft_strdup(s2));
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	cat = malloc(sizeof(char) * (len + 1));
	if (!cat)
		return (NULL);
	while (s1 && s1[i])
	{
		cat[i] = (char)s1[i];
		i++;
	}
	while (s2 && s2[j])
		cat[i++] = (char)s2[j++];
	cat[i] = '\0';
	return (cat);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*dup;

	i = 0;
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}