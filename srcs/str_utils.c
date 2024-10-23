#include <stdio.h>
#include <stdlib.h>


char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	char_c;

	i = 0;
	char_c = (char)c;
	while (s[i])
	{
		if (s[i] == char_c)
			return ((char *) &s[i]);
		i++;
	}
	if (char_c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

