/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:15:09 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:15:48 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

static int	int_len(long n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	number;
	int		len;
	char	*res;
	int		i;

	number = n;
	len = int_len(number);
	res = malloc(len + 1 * sizeof(char));
	alloc_addback(&g_allocs, res);
	if (!res)
		return (NULL);
	res[0] = '0';
	if (number < 0)
		number = -number;
	i = len - 1;
	while (number != 0)
	{
		res[i] = ((number % 10) + '0');
		number = number / 10;
		i--;
	}
	if (n < 0)
		res[0] = '-';
	res[len] = 0;
	return (res);
}

char	*after_dollar_word(char **str, char *whole_word, t_lst *env_lst, int c)
{
	char	*before_word;
	char	*expanded_word;

	while (**str != 0 && !(**str >= 9 && **str <= 13)
		&& !(ft_strchr(" \v\t\r|<>", **str)))
	{
		if (**str == '$')
		{
			whole_word = join_and_free(whole_word, expantion(str, env_lst));
			continue ;
		}
		if (**str == 34 || **str == 39)
		{
			c = **str;
			before_word = make_quoted_word(str, **str, env_lst, NULL);
			if (c == 34)
				expanded_word = expand_quoted_word(before_word, env_lst);
			else
				expanded_word = before_word;
			whole_word = join_and_free(whole_word, expanded_word);
			continue ;
		}
		whole_word = ft_strcat(whole_word, *((*str)++));
	}
	return (whole_word);
}

char	*expand_status_variable(char **str, int status)
{
	char	*word;
	int		i;
	char	c;

	i = 0;
	*str = *str + 2;
	while (*(*str + i) && ft_isalnum(*(*str + i)))
		i++;
	if (i == 0)
		return (ft_itoa(status));
	c = *(*str + i);
	*(*str + i) = 0;
	word = join_and_free(ft_itoa(status), ft_strdup2(*str));
	*(*str + i) = c;
	return (word);
}

char	*expand_qt_word(char *word, t_lst *env_lst)
{
	char	*expanded_word;
	int		i;
	char	*buffer;
	char	*tmp_word;

	buffer = NULL;
	i = 0;
	if (word[i] == 34 || word[i] == 39)
		buffer = get_quotes_buffer(word);
	while (*word && (*word == 34 || *word == 39))
		word++;
	tmp_word = ft_strdup2(word);
	while (tmp_word[i] && tmp_word[i] != 34 && tmp_word[i] != 39)
		i++;
	tmp_word[i] = '\0';
	expanded_word = expand_quoted_word(tmp_word, env_lst);
	if (ft_strlen(buffer) != 0)
	{
		expanded_word = ft_strjoin(buffer, expanded_word);
		expanded_word = ft_strjoin(expanded_word, strrev(buffer));
	}
	return (expanded_word);
}
