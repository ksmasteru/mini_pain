/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aech-chi <aech-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:09:46 by aech-chi          #+#    #+#             */
/*   Updated: 2024/10/13 22:11:06 by aech-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/executer.h"
#include "../includes/parser.h"
#include "../includes/pipes.h"
#include "../includes/tokens.h"
#include "math.h"

bool	not_heredoc(t_token *head)
{
	if (!head)
		return (true);
	while (head->next)
		head = head->next;
	if (head->type == HEREDOC)
		return (false);
	return (true);
}

int	words_lexer(t_token **head, char **str, char *start, t_lst *env_lst)
{
	size_t	length;
	char	*new_word;

	length = 0;
	while (**str && !(ft_strchr(" \t\v\r|><", **str)))
	{
		if (not_heredoc(*head) && (**str == 34 || **str == 39 || **str == '$'))
		{
			if (**str == '$')
			{
				new_word = expand_word(str, start, env_lst, 0);
				split_add_to_env(new_word, head, str);
			}
			else
				new_word = tokenized_quoted_word(str, start, env_lst, head);
			length = 0;
			start = *str;
			continue ;
		}
		*str = *str + 1;
		length++;
	}
	new_word_token(head, str, start, length);
	return (0);
}

t_token	*lexer(char *str, t_lst *env_lst)
{
	char	*start;
	t_token	*head;

	start = str;
	head = NULL;
	while (*str != 0 && *str != '\n')
	{
		while (*str && (ft_strchr(" \t\v\r", *str)))
			str = str + 1;
		start = str;
		while (*str && ft_strchr("|<>", *str))
		{
			add_new_token(&head, &str, start, 1);
			start = str;
		}
		if ((ft_strchr(str, 34) || ft_strchr(str, 39))
			&& (check_balanced_quotes(str) != 0))
		{
			ft_putstr_fd(2, "Error: quotes aren't balanced\n");
			return (NULL);
		}
		if (words_lexer(&head, &str, start, env_lst) < 0)
			return (NULL);
	}
	return (head);
}
