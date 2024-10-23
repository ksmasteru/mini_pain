/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_pars_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:13:13 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:14:46 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc	*g_allocs;

char	*word_till_space(char **str, t_lst *env_lst)
{
	int		i;
	char	*word;
	char	*start;
	int		len;

	start = *str;
	i = 0;
	while (start[i] && !ft_strchr(" \v\t\r", start[i]))
		i++;
	word = (char *)malloc(sizeof(char) * (i + 1));
	alloc_addback(&g_allocs, word);
	word[i] = '\0';
	len = i;
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		*str = *str + 1;
		i++;
	}
	word = expand_quoted_word(word, env_lst);
	return (word);
}

char	*word_till_dollar(char **str, char *start)
{
	int		i;
	char	*word;

	i = 0;
	while (start[i] && start[i] != '$')
	{
		i++;
	}
	word = (char *)malloc(sizeof(char) * (i + 1));
	alloc_addback(&g_allocs, word);
	if (!word)
		return (NULL);
	word[i] = '\0';
	i = 0;
	while (start[i] && start[i] != '$')
	{
		word[i] = start[i];
		i++;
	}
	if (start == *str)
		*str = *str + i;
	return (word);
}

char	*ft_strcat(char *str, char c)
{
	int		len;
	int		i;
	char	*new_str;

	i = -1;
	if (str == NULL)
	{
		new_str = (char *)malloc(sizeof(char) * 2);
		alloc_addback(&g_allocs, new_str);
		new_str[0] = c;
		new_str[1] = 0;
	}
	else
	{
		len = strlen(str) + 1;
		new_str = (char *)malloc(sizeof(char) * len + 1);
		alloc_addback(&g_allocs, new_str);
		new_str[len] = '\0';
		while (++i < len - 1)
			new_str[i] = str[i];
		new_str[i] = c;
	}
	return (new_str);
}

char	*word_till_quotes(char *str, t_lst *env_lst, t_token *head)
{
	int		i;
	int		j;
	int		len;
	char	*res;

	(void)head;
	(void)env_lst;
	j = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			break ;
		i++;
	}
	if (i == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (i + 1));
	alloc_addback(&g_allocs, res);
	len = i;
	i = 0;
	while (i < len)
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}
