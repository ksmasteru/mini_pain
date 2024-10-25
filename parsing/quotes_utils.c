/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:26:04 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:26:22 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

char	*inside_quoted_word(char **str, int c)
{
	int		qoutes_counter;
	char	*inside_quotes_word;
	int		i;

	qoutes_counter = 1;
	i = 0;
	*str = *str + 1;
	inside_quotes_word = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	alloc_addback(&g_allocs, inside_quotes_word);
	inside_quotes_word[ft_strlen(*str) + 1] = '\0';
	inside_quotes_word[i++] = c;
	while (**str != '\0')
	{
		if (**str == c)
			qoutes_counter++;
		inside_quotes_word[i++] = *(*str)++;
		if ((qoutes_counter % 2 == 0 && abs(**str - c) == 5) || (qoutes_counter
				% 2 == 0 && ft_strchr(" \t\v\r|<>;&", **str)))
			break ;
	}
	inside_quotes_word[i] = '\0';
	return (inside_quotes_word);
}

char	*join_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	return (res);
}

char	*get_quoted_word(char **str, int c)
{
	int		qoutes_counter;
	char	*quoted_word;
	int		i;

	if (c != 34 && c != 39)
		return (normal_word(str));
	qoutes_counter = 1;
	i = 0;
	*str = *str + 1;
	quoted_word = (char *)malloc(sizeof(char) * (ft_strlen(*str) + 2));
	alloc_addback(&g_allocs, quoted_word);
	quoted_word[ft_strlen(*str) + 1] = '\0';
	quoted_word[i++] = c;
	while (**str != '\0' && qoutes_counter != 2)
	{
		if (**str == c)
			qoutes_counter++;
		quoted_word[i++] = *(*str)++;
	}
	if (i == 2)
		return (ft_strdup2(""));
	quoted_word[i] = '\0';
	return (quoted_word);
}

char	*get_quotes_buffer(char *word)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = (char *)malloc(sizeof(char) * ft_strlen(word) + 1);
	alloc_addback(&g_allocs, buffer);
	buffer[ft_strlen(word)] = 0;
	while (word[i] && (word[i] == 34 || word[i] == 39))
	{
		buffer[i] = word[i];
		i++;
	}
	buffer[i] = 0;
	return (buffer);
}

char	*strrev(char *str)
{
	int		i;
	int		len;
	char	c;

	len = ft_strlen(str);
	i = 0;
	len--;
	while (i < len / 2)
	{
		c = str[i];
		str[i++] = str[len];
		str[len--] = c;
	}
	return (str);
}
