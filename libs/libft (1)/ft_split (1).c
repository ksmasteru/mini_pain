/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split (1).c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 21:21:36 by sait-alo          #+#    #+#             */
/*   Updated: 2024/10/25 01:23:19 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "tokens.h"

extern t_alloc	*allocs;

static int	count_words(const char *s, char c)
{
	unsigned int	i;
	int				counter;

	i = 0;
	counter = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
			counter++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (counter);
}

static char	**mem_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

static char	**split_helper(char **tab, const char *s, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		j = i;
		if (s[i] == '\0')
			break ;
		while (s[i] && s[i] != c)
			i++;
		tab[k] = ft_substr(s + j, 0, i - j);
		if (!tab[k])
			return (mem_free(tab));
		k++;
	}
	tab[k] = NULL;
	return (tab);
}

{
	char **tab;

	if (!s)
		return (NULL);
	tab = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	return (split_helper(tab, s, c));
}