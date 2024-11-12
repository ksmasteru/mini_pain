/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:06:54 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/25 01:26:49 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

char	*normal_word(char **str)
{
	char	*word;
	int		i;

	i = 0;
	while (*(*str + i) && *(*str + i) != 34 && *(*str + i) != 39
		&& !ft_strchr(" \v\t\r\n|<>;&()", *(*str + i)))
		i++;
	word = (char *)malloc(sizeof(char) * i + 1);
	alloc_addback(&g_allocs, word);
	word[i] = '\0';
	i = 0;
	while (**str && **str != 34 && **str != 39 && !ft_strchr(" \v\t\r\n|<>;&()",
			**str))
	{
		word[i++] = **str;
		*str = *str + 1;
	}
	return (word);
}
// "$HOME $HOME" "$HOME hi"
/*char	*split_expand_word(char	*word)
{
	char	*res;
	char	**splitted_words;
	int		i;
	char	*whole_word;

	whole_word = NULL;
	i = 0;
	splitted_words = ft_split(word, 32);
	split_add_to_allocs(splitted_words);
	while (splitted_words[i])
	{
		if (ft_strchr(splitted_words[i], '$'))
		{
			res = ft_strjoin(whole_word, splitted_words[i]);
		}
	}
}*/

char	*make_quoted_word(char **str, int c, t_lst *env_lst, t_token *head)
{
	char	*whole_word;
	char	*word;

	(void)head;
	whole_word = NULL;
	word = NULL;
	while (**str && !ft_strchr(" \v\t\r\n|<>;&()", **str))
	{
		c = **str;
		word = get_quoted_word(str, c);
		if (word && (c == 34 || c == 39))
			word = clean_quotes_from_word(word, ft_strlen(word), c);
		if (word && ft_strchr(word, '$') && c != 39)
			word = expand_qt_word(word, env_lst);
		whole_word = ft_strjoin(whole_word, word);
	}
	return (whole_word);
}

char	*clean_quotes_from_word(char *quoted_word, int len, int qoute)
{
	char	*clean_word;
	int		i;
	int		x;

	i = 0;
	x = 0;
	clean_word = (char *)malloc(sizeof(char) * (len + 1));
	alloc_addback(&g_allocs, clean_word);
	if (!clean_word)
		return (NULL);
	clean_word[len] = '\0';
	while (quoted_word[i] != '\0')
	{
		if (quoted_word[i] != qoute)
			clean_word[x++] = quoted_word[i++];
		else
			i++;
	}
	clean_word[x] = '\0';
	return (clean_word);
}

char	*qouted_word(char **str, char *start, t_lst *env_lst, t_token *head)
{
	char	*word_before_qoutes;
	char	*complete_word;
	char	*qouted_word;

	word_before_qoutes = word_till_quotes(start, env_lst, head);
	while (**str)
	{
		if (**str == 34 || **str == 39)
			break ;
		*str = *str + 1;
	}
	qouted_word = make_quoted_word(str, **str, env_lst, head);
	complete_word = join_and_free(word_before_qoutes, qouted_word);
	return (complete_word);
}

char	*expand_quoted_word(char *str, t_lst *env_lst)
{
	char	*whole_word;

	whole_word = NULL;
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == '$')
		{
			whole_word = join_and_free(whole_word, expantion(&str, env_lst));
			continue ;
		}
		else
			whole_word = ft_strcat(whole_word, *str);
		str++;
	}
	return (whole_word);
}
