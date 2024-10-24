/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:04:07 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:05:03 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

extern t_alloc *g_allocs;

char *expand_word(char **str, char *start, t_lst *env_lst,
				  char closing_quotes)
{
	char *before_word;
	char *expanded_word;
	char *whole_word;

	expanded_word = NULL;
	(void)closing_quotes;
	whole_word = NULL;
	before_word = word_till_dollar(str, start);
	if (**str == '$' && *(*str + 1) == '?')
		expanded_word = expand_status_variable(str, env_lst->status);
	else if (**str == '$' && *(*str + 1) == '$')
	{
		*str = *str + 2;
		return (ft_strjoin(before_word, ft_strdup2("")));
	}
	else
		expanded_word = expantion(str, env_lst);
	whole_word = join_and_free(before_word, expanded_word);
	if (**str != 0 && **str != 32 && !(**str >= 9 && **str <= 13) && !(strchr("|<>", **str)))
		return (after_dollar_word(str, whole_word, env_lst, 0));
	return (whole_word);
}

char *close_expanded_word(char *whole_word, char **str)
{
	int i;
	char *quotes;
	int len;

	i = 0;
	while (*(*str + i) != 0)
		i++;
	quotes = (char *)malloc(sizeof(char) * i + 1);
	alloc_addback(&g_allocs, quotes);
	quotes[i] = '\0';
	len = i;
	i = 0;
	while (i < len)
	{
		quotes[i++] = **str;
		*str = *str + 1;
	}
	return (ft_strjoin(whole_word, quotes));
}

int expantion_check_quotes(char **str, t_lst *env_lst, char **expanded_word)
{
	int i;

	i = 0;
	if (**str == 34 || **str == 39)
	{
		*expanded_word = make_quoted_word(str, **str, env_lst, NULL);
		return (-1);
	}
	else
	{
		while (*(*str + i) != 0 && *(*str + i) != '$' && *(*str + i) != 34 && *(*str + i) != 39 && *(*str + i) != 32 && !(*(*str + i) >= 9 && *(*str + i) <= 13) && !(strchr("|><", *(*str + i))))
			i++;
	}
	return (i);
}

char *expantion(char **str, t_lst *env_lst)
{
	int i;
	char *expand_word;
	int len;
	char *expanded_word;

	if (**str != '$')
		return (NULL);
	*str = *str + 1;
	i = expantion_check_quotes(str, env_lst, &expanded_word);
	if (i == 0)
		return (ft_strdup2("$"));
	else if (i == -1)
		return (expanded_word);
	len = i;
	expand_word = (char *)malloc(sizeof(char) * len + 1);
	alloc_addback(&g_allocs, expand_word);
	expand_word[len] = '\0';
	i = 0;
	while (i < len)
	{
		expand_word[i++] = **str;
		*str = *str + 1;
	}
	expanded_word = get_expanded_word(expand_word, env_lst);
	return (expanded_word);
}

char *get_expanded_word(char *expand_word, t_lst *env_lst)
{
	char *expanded_word;

	expanded_word = NULL;
	while (env_lst)
	{
		if (strcmp(env_lst->data, expand_word) == 0)
		{
			if (env_lst->value)
			{
				expanded_word = (char *)malloc(sizeof(char) * strlen(env_lst->value->data) + 1);
				alloc_addback(&g_allocs, expanded_word);
				expanded_word[strlen(env_lst->value->data)] = '\0';
				expanded_word = strncpy(expanded_word, env_lst->value->data,
										strlen(env_lst->value->data));
				return (expanded_word);
			}
			else
			{
				return (NULL);
			}
		}
		env_lst = env_lst->next;
	}
	return (NULL);
}
